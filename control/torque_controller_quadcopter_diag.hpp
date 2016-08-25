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
 * \file torque_controller_quadcopter_diag.hpp
 *
 * \author MAV'RIC Team
 * \author Julien Lecoeur
 * \author Nicolas Dousse
 * \author Basil Huber
 *
 * \brief Links between torque commands and servos PWM command for quadcopters
 * in diagonal configuration
 *
 ******************************************************************************/


#ifndef TORQUE_CONTROLLER_QUADCOPTER_DIAG_HPP_
#define TORQUE_CONTROLLER_QUADCOPTER_DIAG_HPP_

#include "control/torque_controller.hpp"


class Torque_controller_quadcopter_diag : public Torque_controller
{
public:

    /**
     * \brief Configuration
     */
    struct conf_t
    {
        rot_dir_t   motor_rear_left_dir;        ///< Rear  motor turning direction
        rot_dir_t   motor_front_left_dir;       ///< Left  motor turning direction
        rot_dir_t   motor_front_right_dir;      ///< Front motor turning direction
        rot_dir_t   motor_rear_right_dir;       ///< Right motor turning direction
        Torque_controller::conf_t torque_controller_config; ///< Config for parent class
    };

    /**
     * \brief Constructor arguments
     */
    struct args_t
    {
        Servo& motor_rear_left;
        Servo& motor_front_left;
        Servo& motor_front_right;
        Servo& motor_rear_right;
    };   

    /**
     * \brief                   Constructor (calls only super class constructor)
     *
     * \param motor_rear_left   Rear left motor
     * \param motor_front_left  Front left motor
     * \param motor_front_right Front right motor
     * \param motor_rear_right  Rear right motor
     * \param config            configuration
     */
    Torque_controller_quadcopter_diag(args_t args, const conf_t& config = default_config());


    /*
     * \brief   Write motor commands to servo structure based on torque command
     */
    virtual void update();

    static inline conf_t default_config();

private:
    rot_dir_t   motor_rear_left_dir_;            ///< Rear  motor turning direction
    rot_dir_t   motor_front_left_dir_;           ///< Left  motor turning direction
    rot_dir_t   motor_front_right_dir_;          ///< Front motor turning direction
    rot_dir_t   motor_rear_right_dir_;           ///< Right motor turning direction
    Servo&      motor_rear_left_;                ///< Servo for rear left motor
    Servo&      motor_front_left_;               ///< Servo for front left motor
    Servo&      motor_front_right_;              ///< Servo for front right motor
    Servo&      motor_rear_right_;               ///< Servo for rear right motor
};

Torque_controller_quadcopter_diag::conf_t Torque_controller_quadcopter_diag::default_config()
{
    conf_t conf;

    conf.motor_rear_left_dir                 = CCW;
    conf.motor_front_left_dir                = CW;
    conf.motor_front_right_dir               = CCW;
    conf.motor_rear_right_dir                = CW;
    conf.torque_controller_config            = {};
    conf.torque_controller_config.min_thrust = -0.9f;
    conf.torque_controller_config.max_thrust = 1.0f;

    return conf;
}

#endif /* TORQUE_CONTROLLER_QUADCOPTER_DIAG_HPP_ */
