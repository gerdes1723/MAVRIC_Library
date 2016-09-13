/*******************************************************************************
 * Copyright (c) 2009-2016, MAV'RIC Development Team
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/*******************************************************************************
 * \file mavlink_communication.hpp
 *
 * \author MAV'RIC Team
 * \author Julien Lecoeur
 *
 * \brief This module handles various aspect of mavlink protocol with periodic telemetry,
 *        message callback, and onboard parameters
 *
 ******************************************************************************/


#ifndef MAVLINK_COMMUNICATION_HPP_
#define MAVLINK_COMMUNICATION_HPP_

#include "communication/mavlink_stream.hpp"
#include "communication/periodic_telemetry.hpp"
#include "communication/onboard_parameters.hpp"
#include "communication/mavlink_message_handler.hpp"


/**
 * \brief   Handles various aspect of mavlink protocol with periodic telemetry, message callback,
 *          and onboard parameters
 */
template<uint32_t N_TELEM, uint32_t N_MSG_CB, uint32_t N_CMD_CB, uint32_t N_PARAM>
class Mavlink_communication_T
{
public:

    /**
     * \brief   Configuration of the module Mavlink Communication
     */
    struct conf_t
    {
        Mavlink_stream::conf_t          mavlink_stream_config;          ///<    Configuration for the module MAVLink stream
        Periodic_telemetry::conf_t      telemetry_config;               ///<    Configuration the the module periodic telemetry
        Mavlink_message_handler::conf_t message_handler_config;         ///<    Configuration for the module message handler
        Onboard_parameters::conf_t      onboard_parameters_config;      ///<    Configuration for the module onboard parameters
    };

    /**
     * \brief   Default configuration
     *
     * \param   sysid       System id (default value = 1)
     *
     * \return  Config structure
     */
    static inline conf_t default_config(uint8_t sysid = 1)
    {
        conf_t conf                       = {};

        conf.mavlink_stream_config        = {};
        conf.mavlink_stream_config.sysid  = sysid;
        conf.mavlink_stream_config.compid = 50;
        conf.mavlink_stream_config.debug  = false,

        conf.telemetry_config             = Periodic_telemetry::default_config();
        conf.message_handler_config       = Mavlink_message_handler::default_config();
        conf.onboard_parameters_config    = Onboard_parameters::default_config();

        return conf;
    };

    /**
     * \brief   Initialisation of the module MAVLink communication
     *
     * \param   config                  Configuration
     * \param   serial                  Input/Output stream
     * \param   state                   MAV state
     * \param   file_storage            File used to store parameters between files
     *
     * \return  True if the init succeed, false otherwise
     */
    Mavlink_communication_T(Serial& serial, State& state, File& file_storage, const conf_t& config = default_config()):
        mavlink_stream_(serial, config.mavlink_stream_config),
        telemetry_(mavlink_stream_, config.telemetry_config),
        handler_(mavlink_stream_, config.message_handler_config),
        parameters_(file_storage, state, handler_, mavlink_stream_, config.onboard_parameters_config)
    {
        bool init_success = true;

        // Add callback to activate / disactivate streams
        Mavlink_message_handler::msg_callback_t callback;

        callback.message_id     = MAVLINK_MSG_ID_REQUEST_DATA_STREAM; // 66
        callback.sysid_filter   = MAVLINK_BASE_STATION_ID;
        callback.compid_filter  = MAV_COMP_ID_ALL;
        callback.function       = (Mavlink_message_handler::msg_callback_func_t)       &Periodic_telemetry::toggle_telemetry_stream;
        callback.module_struct  = (Mavlink_message_handler::handling_module_struct_t)  &telemetry_;

        init_success &= handler_.add_msg_callback(&callback);

        if(!init_success)
        {
            print_util_dbg_print("[MAVLINK COMMUNICATION] constructor error\r\n");
        }
    }

    /**
     * \brief   Returns sysid of the underlying mavlink_stream
     *
     *
     * \return  sysid of the underlying mavlink_stream
     */
    uint32_t sysid()
    {
        return mavlink_stream_.sysid();
    }


    /*
     * \brief   Returns periodic telemetry
     */
    Periodic_telemetry& telemetry()
    {
        return telemetry_;
    }
    Periodic_telemetry* p_telemetry()
    {
        return &telemetry_;
    }

    /*
     * \brief   Returns message_handler
     */
    Mavlink_message_handler& handler()
    {
        return handler_;
    }
    Mavlink_message_handler* p_handler()
    {
        return &handler_;
    }

    /*
     * \brief   Returns mavlink_stream
     */
    Mavlink_stream& stream()
    {
        return mavlink_stream_;
    }
    Mavlink_stream* p_stream()
    {
        return &mavlink_stream_;
    }


    /*
     * \brief   Returns onboard_parameters struct
     */
    Onboard_parameters& parameters()
    {
        return parameters_;
    }


    /**
     * \brief   Main update function
     *
     * \return  Success
     */
    bool update(void)
    {
        // Receive new message
        Mavlink_stream::msg_received_t rec;
        while (mavlink_stream_.receive(&rec))
        {
                handler_.receive(&rec);
        }

        // Send messages
        telemetry_.update();

        // Send one onboard param, if necessary
        parameters_.send_first_scheduled_parameter();

        return true;
    }


    /**
     * \brief   Main update function, static version
     *
     * \param   mavlink_communication   Pointer to the MAVLink communication structure
     *
     * \return  Success
     */
    static bool update_task(Mavlink_communication_T* mavlink_communication)
    {
        return mavlink_communication->update();
    }

private:
    Mavlink_stream                                  mavlink_stream_;       ///<    Mavlink interface using streams
    Periodic_telemetry_T<N_TELEM>                   telemetry_;            ///<    Periodic telemetry
    Mavlink_message_handler_T<N_MSG_CB, N_CMD_CB>   handler_;              ///<    Message handler
    Onboard_parameters_T<N_PARAM>                   parameters_;           ///<    Onboard parameters
};


#endif /* MAVLINK_COMMUNICATION_HPP_ */
