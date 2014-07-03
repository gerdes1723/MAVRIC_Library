/** 
 * \page The MAV'RIC license
 *
 * The MAV'RIC Framework
 *
 * Copyright © 2011-2014
 *
 * Laboratory of Intelligent Systems, EPFL
 */


/**
 * \file imu.c
 *
 * This file implements the code to read the IMU data
 */


#include "imu.h"

#include "qfilter.h"
#include "delay.h"
#include "itg3200_driver.h"
#include "adxl345_driver.h"
#include "lsm330dlc_driver.h"

#include "compass_hmc5883l.h"
#include "time_keeper.h"
#include "print_util.h"
#include "position_estimation.h"
#include "mavlink_stream.h"


int ic;
void imu_init (Imu_Data_t *imu1)
{
	//itg3200_driver_init_slow();
	//adxl345_driver_init_slow();
	lsm330dlc_driver_init();
	print_util_dbg_print("LSM330 initialised\n");	
	
	compass_hmc58831l_init_slow();

	//imu_calibrate_Gyros(imu1);
	imu1->raw_scale[X + GYRO_OFFSET] =  RAW_GYRO_X_SCALE;
	imu1->raw_scale[Y + GYRO_OFFSET] =  RAW_GYRO_Y_SCALE;
	imu1->raw_scale[Z + GYRO_OFFSET] =  RAW_GYRO_Z_SCALE;
	imu1->raw_scale[X + ACC_OFFSET] =  RAW_ACC_X_SCALE;
	imu1->raw_scale[Y + ACC_OFFSET] =  RAW_ACC_Y_SCALE;
	imu1->raw_scale[Z + ACC_OFFSET] =  RAW_ACC_Z_SCALE;
	imu1->raw_scale[X + COMPASS_OFFSET] =  RAW_MAG_X_SCALE;
	imu1->raw_scale[Y + COMPASS_OFFSET] =  RAW_MAG_Y_SCALE;
	imu1->raw_scale[Z + COMPASS_OFFSET] =  RAW_MAG_Z_SCALE;
	imu1->raw_bias[X + GYRO_OFFSET] = 0.0f;
	imu1->raw_bias[Y + GYRO_OFFSET] = 0.0f;
	imu1->raw_bias[Z + GYRO_OFFSET] = 0.0f;
	
	// acceleration biais
	imu1->raw_bias[X + ACC_OFFSET] = ACC_BIAIS_X;
	imu1->raw_bias[Y + ACC_OFFSET] = ACC_BIAIS_Y;
	imu1->raw_bias[Z + ACC_OFFSET] = ACC_BIAIS_Z;
	
	// magneto bias
	imu1->raw_bias[X + COMPASS_OFFSET] = MAG_BIAIS_X;
	imu1->raw_bias[Y + COMPASS_OFFSET] = MAG_BIAIS_Y;
	imu1->raw_bias[Z + COMPASS_OFFSET] = MAG_BIAIS_Z;
	
	imu_last_update_init = false;
}


void imu_get_raw_data(Imu_Data_t *imu1)
{
	//gyro_data* gyros = itg3200_driver_get_data_slow();
	//acc_data* accs = adxl345_driver_get_acc_data_slow();
	lsm_gyro_data_t* gyros = lsm330dlc_driver_get_gyro_data();
	lsm_acc_data_t* accs = lsm330dlc_driver_get_acc_data();
	compass_data* compass = compass_hmc58831l_get_data_slow();


	imu1->raw_channels[GYRO_OFFSET + IMU_X] = (float)gyros->axes[RAW_GYRO_X] * GYRO_AXIS_X;
	imu1->raw_channels[GYRO_OFFSET + IMU_Y] = (float)gyros->axes[RAW_GYRO_Y] * GYRO_AXIS_Y;
	imu1->raw_channels[GYRO_OFFSET + IMU_Z] = (float)gyros->axes[RAW_GYRO_Z] * GYRO_AXIS_Z;

	imu1->raw_channels[ACC_OFFSET + IMU_X] = ((float)accs->axes[RAW_ACC_X]) * ACC_AXIS_X;
	imu1->raw_channels[ACC_OFFSET + IMU_Y] = ((float)accs->axes[RAW_ACC_Y]) * ACC_AXIS_Y;
	imu1->raw_channels[ACC_OFFSET + IMU_Z] = ((float)accs->axes[RAW_ACC_Z]) * ACC_AXIS_Z;
	
	imu1->raw_channels[COMPASS_OFFSET + IMU_X] = (float)compass->axes[RAW_MAG_X] * MAG_AXIS_X;
	imu1->raw_channels[COMPASS_OFFSET + IMU_Y] = (float)compass->axes[RAW_MAG_Y] * MAG_AXIS_Y;
	imu1->raw_channels[COMPASS_OFFSET + IMU_Z] = (float)compass->axes[RAW_MAG_Z] * MAG_AXIS_Z;
}

void imu_calibrate_Gyros(Imu_Data_t *imu1)
{
	int i,j;
	imu_get_raw_data(imu1);
	
	for (j = 0; j < 3; j++)
	{
		imu1->raw_bias[j] = (float)imu1->raw_channels[j];
	}
	
	for (i = 0; i < 100; i++)
	{
		imu_get_raw_data(imu1);

		//imu1->raw_bias[0 + ACC_OFFSET] = (0.9f * imu1->raw_bias[0 + ACC_OFFSET] + 0.1f * (float)imu1->raw_channels[0 + ACC_OFFSET]);
		//imu1->raw_bias[1 + ACC_OFFSET] = (0.9f * imu1->raw_bias[1 + ACC_OFFSET] + 0.1f * (float)imu1->raw_channels[1 + ACC_OFFSET]);
		//imu1->raw_bias[2 + ACC_OFFSET] = (0.9f * imu1->raw_bias[2 + ACC_OFFSET] + 0.1f * ((float)imu1->raw_channels[2 + ACC_OFFSET] - imu1->raw_scale[2 + ACC_OFFSET]));
		for (j = 0; j < 3; j++)
		{
			imu1->raw_bias[j] = (0.9f * imu1->raw_bias[j] + 0.1f * (float)imu1->raw_channels[j]);
			//imu1->attitude.raw_mag_mean[j] = (1.0 - fMAG_LPF) * imu1->attitude.raw_mag_mean[j] + MAG_LPF * ((float)imu1->raw_channels[j + COMPASS_OFFSET]);
		}
	
		delay_ms(4);
	}
}

void imu_update(Imu_Data_t *imu1, position_estimator_t *pos_est, pressure_data *barometer, gps_Data_type *gps)
{
	uint32_t t = time_keeper_get_time_ticks();
	
	if (!imu_last_update_init)
	{
		imu1->last_update = t;
		imu_last_update_init = true;
	}
	else
	{
		imu1->dt = time_keeper_ticks_to_seconds(t - imu1->last_update);
		imu1->last_update = t;
		qfilter_attitude_estimation(&imu1->attitude, &imu1->raw_channels, imu1->dt);
		if (imu1->attitude.calibration_level == OFF)
		{
			position_estimation_position_integration(pos_est, &imu1->attitude, imu1->dt);
			position_estimation_position_correction(pos_est, barometer, gps, imu1->dt);
		}
	}
}