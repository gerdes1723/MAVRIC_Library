/*******************************************************************************
 * Copyright (c) 2009-2014, MAV'RIC Development Team
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
 * \file MAV011_imu_config.h
 * 
 * \author MAV'RIC Team
 *   
 * \brief This file defines the mapping between the IMU and the compass and the 
 * frames of the vehicles as well as the scales and the biaises. 
 * The NED frame is used.
 *
 ******************************************************************************/


#ifndef CONF_IMU_REV4_H_
#define CONF_IMU_REV4_H_

#include "imu.hpp"
#include "megafly_rev4.hpp"

static inline imu_conf_t imu_config(void)
{
	imu_conf_t conf	= megafly_rev4_default_config().imu_config;

	// Accelerometer Bias
	conf.accelerometer.bias[0] = 100.0f / 4000.0;
	conf.accelerometer.bias[1] = 110.0f / 4000.0;
	conf.accelerometer.bias[2] = 400.0f / 4000.0;
	
	// Gyroscope Bias
	conf.gyroscope.bias[0] = -0.56f / 818.5111;
	conf.gyroscope.bias[1] =  7.00f / 818.5111;
	conf.gyroscope.bias[2] = -4.66f / 818.5111;
	
	// Magnetometer Bias
	conf.magnetometer.bias[0] = 280.6f / 600.0;
	conf.magnetometer.bias[1] =-115.5f / 600.0;
	conf.magnetometer.bias[2] =-260.5f / 600.0;

	return conf;
}

#endif /* CONF_IMU_REV4_H_ */