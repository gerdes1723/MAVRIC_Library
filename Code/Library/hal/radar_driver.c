#include "radar_driver.h"



void radar_driver_init(void) {
	gpio_configure_pin(RADAR_POWER1_PIN, GPIO_DIR_OUTPUT);	
	gpio_configure_pin(RADAR_POWER2_PIN, GPIO_DIR_OUTPUT);
	radar_driver_switch_power(0,0);
}

void radar_driver_switch_power(int supply1, int supply2) {
	if (supply1 == 0) {
		gpio_set_pin_low(RADAR_POWER1_PIN);
	} else {
		gpio_set_pin_high(RADAR_POWER1_PIN);
	}
	if (supply2 == 0) {
		gpio_set_pin_low(RADAR_POWER2_PIN);
	} else {
		gpio_set_pin_high(RADAR_POWER2_PIN);
	}
}



