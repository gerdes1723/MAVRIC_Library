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
 * \file state_telemetry.c
 *
 * \author MAV'RIC Team
 * \author Nicolas Dousse
 *
 * \brief This module takes care of sending periodic telemetric messages for
 * the state
 *
 ******************************************************************************/


//#include "communication/state_telemetry.hpp"
#include "communication/offboard_camera_telemetry.hpp"

extern "C"
{
#include "util/print_util.h"
#include "hal/common/time_keeper.hpp"
}

//------------------------------------------------------------------------------
// PRIVATE FUNCTIONS DECLARATION
//------------------------------------------------------------------------------

/**
 * \brief                       Receives information related to the camera results
 *
 * \param   camera              The pointer to the offboard camera class
 * \param   sysid               The system ID
 * \param   msg                 The received MAVLink message structure
 */
//void offboard_camera_telemetry_receive_camera_output(Offboard_Camera* camera, uint32_t sysid, mavlink_message_t* msg);
static mav_result_t offboard_camera_telemetry_receive_camera_output(Offboard_Camera* camera, mavlink_command_long_t* packet);
//------------------------------------------------------------------------------
// PRIVATE FUNCTIONS IMPLEMENTATION
//------------------------------------------------------------------------------

//void offboard_camera_telemetry_receive_camera_output(Offboard_Camera* camera, uint32_t sysid, mavlink_message_t* msg)
static mav_result_t offboard_camera_telemetry_receive_camera_output(Offboard_Camera* camera, mavlink_command_long_t* packet)
{
    mav_result_t result;
    print_util_dbg_init_msg("[PICAMERA MSG RECV]", true);
    print_util_dbg_print("Param1: ");
    print_util_dbg_print_num(packet->param1,10);
    print_util_dbg_print("\r\n");
    print_util_dbg_print("Param2: ");
    print_util_dbg_print_num(packet->param2,10);
    print_util_dbg_print("\r\n");
    print_util_dbg_print("Param3: ");
    print_util_dbg_print_num(packet->param3,10);
    print_util_dbg_print("\r\n");
    print_util_dbg_print("Param4: ");
    print_util_dbg_print_num(packet->param4,10);
    print_util_dbg_print("\r\n");
    print_util_dbg_print("Param5: ");
    print_util_dbg_print_num(packet->param5,10);
    print_util_dbg_print("\r\n");
    print_util_dbg_print("Param6: ");
    print_util_dbg_print_num(packet->param6,10);
    print_util_dbg_print("\r\n");
    print_util_dbg_print("Param7: ");
    print_util_dbg_print_num(packet->param7,10);
    print_util_dbg_print("\r\n");
    result = MAV_RESULT_ACCEPTED;
    return result;

}

//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS IMPLEMENTATION
//------------------------------------------------------------------------------

bool offboard_camera_telemetry_init(Offboard_Camera* camera, mavlink_message_handler_t* message_handler)
{
    bool init_success = true;

    // Add callbacks for cmd
    mavlink_message_handler_cmd_callback_t callbackcmd;
    callbackcmd.command_id = MAV_CMD_DO_CONTROL_VIDEO; // 200
    callbackcmd.sysid_filter = MAV_SYS_ID_ALL;
    callbackcmd.compid_filter = MAV_COMP_ID_ALL;
    callbackcmd.compid_target = MAV_COMP_ID_ALL; // WRONG 190
    callbackcmd.function = (mavlink_cmd_callback_function_t)    &offboard_camera_telemetry_receive_camera_output;
    callbackcmd.module_struct =                                 camera;
    init_success &= mavlink_message_handler_add_cmd_callback(message_handler, &callbackcmd);
    print_util_dbg_init_msg("[PICAMERA TELEMETRY INIT]", init_success);
    return init_success;
}

void offboard_camera_telemetry_send_start_stop(const Offboard_Camera* camera, const mavlink_stream_t* mavlink_stream, mavlink_message_t* msg)
{
    int is_camera_running = -1;
    switch(camera->is_camera_running_)
    {
        case true:
            is_camera_running = 1;
            break;
        case false:
            is_camera_running = 0;
            break;
    }
    mavlink_msg_command_long_pack(  mavlink_stream->sysid,      // system_id
                                    mavlink_stream->compid,     // component_id
                                    msg,                        // mavlink_msg
                                    0,      // target_system
                                    0,      // target_component
                                    MAV_CMD_DO_CONTROL_VIDEO,   // command
                                    0,     // confirmation
                                    camera->camera_id_,    // param1
                                    is_camera_running,          // param2
                                    0,                          // param3
                                    0,                          // param4
                                    0,                          // param5
                                    0,                          // param6
                                    0);                         // param7
}