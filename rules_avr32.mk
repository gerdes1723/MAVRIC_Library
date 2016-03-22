CFLAGS   += -D__MAVRIC_ENDIAN_BIG__
CXXFLAGS += -D__MAVRIC_ENDIAN_BIG__

LIB_SRCS += boards/megafly_rev4/megafly_rev4.cpp

LIB_SRCS += hal/avr32/adc_avr32.cpp          
LIB_SRCS += hal/avr32/adc_int.c          
LIB_SRCS += hal/avr32/analog_monitor.c            
LIB_SRCS += hal/avr32/analog_monitor_telemetry.cpp                  
LIB_SRCS += hal/avr32/dac_dma.c
LIB_SRCS += hal/avr32/i2c_avr32.cpp            
LIB_SRCS += hal/avr32/led.c            
LIB_SRCS += hal/avr32/led_avr32.cpp            
LIB_SRCS += hal/avr32/gpio_avr32.cpp
LIB_SRCS += hal/avr32/piezo_speaker.c        
LIB_SRCS += hal/avr32/pwm_avr32.cpp
LIB_SRCS += hal/avr32/serial_avr32.cpp
LIB_SRCS += hal/avr32/serial_usb_avr32.cpp
LIB_SRCS += hal/avr32/spi_avr32.cmegapp
LIB_SRCS += hal/avr32/sd_spi.c
LIB_SRCS += hal/avr32/time_keeper.c
LIB_SRCS += hal/avr32/file_flash_avr32.cpp
LIB_SRCS += hal/avr32/file_fat_fs.cpp
LIB_SRCS += hal/avr32/fat_fs_mounting.cpp
LIB_SRCS += hal/avr32/FatFs/atadrive.c
LIB_SRCS += hal/avr32/FatFs/sdcard.c
LIB_SRCS += hal/avr32/FatFs/usbdisk.c
LIB_SRCS += communication/offboard_camera_telemetry.cpp
LIB_SRCS += sensing/offboard_camera.cpp



LIB_MEGAFLY_INC += boards/megafly_rev4

# ------------------------------------------------------------------------------
# ASF Library
# ------------------------------------------------------------------------------

LIB_ASF_INC += libs/asf
LIB_ASF_INC += libs/asf/avr32
LIB_ASF_INC += libs/asf/avr32/services
LIB_ASF_INC += libs/asf/avr32/services/dsp
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/include
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/programs
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/programs/data_extract
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/programs/data_extract/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/programs/data_get
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/programs/data_get/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/programs/adpcm_encode
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/programs/adpcm_encode/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/programs/adpcm_streaming
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/programs/adpcm_streaming/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/programs/data_print
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/programs/data_print/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/print_complex_vect
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/print_complex_vect/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/serial_scope
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/serial_scope/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/resampling_coefficients_generation
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/resampling_coefficients_generation/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/benchmark
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/benchmark/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/benchmark/resources
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/print_real_vect
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/print_real_vect/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/adpcm_encoder
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/adpcm_encoder/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/twiddle_factors_generator
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/utils/scripts/twiddle_factors_generator/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/at32uc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/at32uc/docsrc
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/at32uc/basic
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/at32uc/basic/transforms
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/at32uc/basic/filters
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/at32uc/basic/operators
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/at32uc/basic/vectors
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/generic
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/generic/advanced
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/generic/advanced/resampling
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/generic/advanced/adpcm
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/generic/basic
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/generic/basic/transforms
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/generic/basic/filters
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/generic/basic/operators
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/generic/basic/windowing
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/generic/basic/vectors
LIB_ASF_INC += libs/asf/avr32/services/dsp/dsplib/generic/basic/signal_generation
LIB_ASF_INC += libs/asf/avr32/services/delay
LIB_ASF_INC += libs/asf/avr32/utils
LIB_ASF_INC += libs/asf/avr32/utils/startup
LIB_ASF_INC += libs/asf/avr32/utils/libs
LIB_ASF_INC += libs/asf/avr32/utils/libs/dsplib
LIB_ASF_INC += libs/asf/avr32/utils/libs/dsplib/include
LIB_ASF_INC += libs/asf/avr32/utils/libs/dsplib/at32ucr3fp
LIB_ASF_INC += libs/asf/avr32/utils/libs/dsplib/at32ucr3fp/gcc
LIB_ASF_INC += libs/asf/avr32/utils/preprocessor
LIB_ASF_INC += libs/asf/avr32/drivers
LIB_ASF_INC += libs/asf/avr32/drivers/pm
LIB_ASF_INC += libs/asf/avr32/drivers/adcifa
LIB_ASF_INC += libs/asf/avr32/drivers/usart
LIB_ASF_INC += libs/asf/avr32/drivers/twim
LIB_ASF_INC += libs/asf/avr32/drivers/intc
LIB_ASF_INC += libs/asf/avr32/drivers/ast
LIB_ASF_INC += libs/asf/avr32/drivers/pevc
LIB_ASF_INC += libs/asf/avr32/drivers/tc
LIB_ASF_INC += libs/asf/avr32/drivers/spi
LIB_ASF_INC += libs/asf/avr32/drivers/usbc
LIB_ASF_INC += libs/asf/avr32/drivers/pdca
LIB_ASF_INC += libs/asf/avr32/drivers/cpu
LIB_ASF_INC += libs/asf/avr32/drivers/cpu/cycle_counter
LIB_ASF_INC += libs/asf/avr32/drivers/eic
LIB_ASF_INC += libs/asf/avr32/drivers/dacifb
LIB_ASF_INC += libs/asf/avr32/drivers/pwm
LIB_ASF_INC += libs/asf/avr32/drivers/flashc
LIB_ASF_INC += libs/asf/avr32/drivers/gpio
LIB_ASF_INC += libs/asf/avr32/drivers/twis
LIB_ASF_INC += libs/asf/avr32/drivers/scif
LIB_ASF_INC += libs/asf/common
LIB_ASF_INC += libs/asf/common/services
LIB_ASF_INC += libs/asf/common/services/usb
LIB_ASF_INC += libs/asf/common/services/usb/udc
LIB_ASF_INC += libs/asf/common/services/usb/class
LIB_ASF_INC += libs/asf/common/services/usb/class/cdc
LIB_ASF_INC += libs/asf/common/services/usb/class/cdc/device
LIB_ASF_INC += libs/asf/common/services/clock
LIB_ASF_INC += libs/asf/common/services/clock/uc3c
LIB_ASF_INC += libs/asf/common/services/serial
LIB_ASF_INC += libs/asf/common/services/serial/uc3_usart
LIB_ASF_INC += libs/asf/common/services/spi
LIB_ASF_INC += libs/asf/common/services/spi/uc3_spi
LIB_ASF_INC += libs/asf/common/services/twi
LIB_ASF_INC += libs/asf/common/services/twi/uc3_twim
LIB_ASF_INC += libs/asf/common/services/sleepmgr
LIB_ASF_INC += libs/asf/common/services/sleepmgr/uc3
LIB_ASF_INC += libs/asf/common/utils
LIB_ASF_INC += libs/asf/common/utils/stdio
LIB_ASF_INC += libs/asf/common/utils/stdio/stdio_usb
LIB_ASF_INC += libs/asf/common/utils/stdio/stdio_serial
LIB_ASF_INC += libs/asf/common/utils/interrupt
LIB_ASF_INC += libs/asf/common/boards
LIB_ASF_INC += libs/asf/common/boards/user_board

LIB_SRCS += libs/asf/avr32/drivers/intc/exception_noNMI.S
LIB_SRCS += libs/asf/avr32/utils/startup/startup_uc3.S
LIB_SRCS += libs/asf/avr32/utils/startup/trampoline_uc3.S
LIB_SRCS += libs/asf/avr32/drivers/adcifa/adcifa.c
LIB_SRCS += libs/asf/avr32/drivers/ast/ast.c
LIB_SRCS += libs/asf/avr32/drivers/dacifb/dacifb.c
LIB_SRCS += libs/asf/avr32/drivers/eic/eic.c
LIB_SRCS += libs/asf/avr32/drivers/flashc/flashc.c
LIB_SRCS += libs/asf/avr32/drivers/gpio/gpio.c
LIB_SRCS += libs/asf/avr32/drivers/intc/intc.c
LIB_SRCS += libs/asf/avr32/drivers/pdca/pdca.c
LIB_SRCS += libs/asf/avr32/drivers/pevc/pevc.c
LIB_SRCS += libs/asf/avr32/drivers/pm/pm_uc3c.c  
LIB_SRCS += libs/asf/avr32/drivers/pm/power_clocks_lib.c
LIB_SRCS += libs/asf/avr32/drivers/pwm/pwm4.c
LIB_SRCS += libs/asf/avr32/drivers/scif/scif_uc3c.c
LIB_SRCS += libs/asf/avr32/drivers/spi/spi.c
LIB_SRCS += libs/asf/avr32/drivers/tc/tc.c
LIB_SRCS += libs/asf/avr32/drivers/twim/twim.c
LIB_SRCS += libs/asf/avr32/drivers/usart/usart.c
LIB_SRCS += libs/asf/avr32/drivers/usbc/usbc_device.c
LIB_SRCS += libs/asf/avr32/services/delay/delay.c
LIB_SRCS += libs/asf/avr32/utils/startup/startup_uc3.S
LIB_SRCS += libs/asf/common/boards/user_board/init.c
LIB_SRCS += libs/asf/common/services/clock/uc3c/osc.c
LIB_SRCS += libs/asf/common/services/clock/uc3c/pll.c
LIB_SRCS += libs/asf/common/services/clock/uc3c/sysclk.c
LIB_SRCS += libs/asf/common/services/sleepmgr/uc3/sleepmgr.c
LIB_SRCS += libs/asf/common/services/spi/uc3_spi/spi_master.c
LIB_SRCS += libs/asf/common/services/usb/class/cdc/device/udi_cdc.c
LIB_SRCS += libs/asf/common/services/usb/class/cdc/device/udi_cdc_desc.c
LIB_SRCS += libs/asf/common/services/usb/udc/udc.c
LIB_SRCS += libs/asf/common/utils/stdio/read.c
LIB_SRCS += libs/asf/common/utils/stdio/write.c
LIB_SRCS += libs/asf/common/utils/stdio/stdio_usb/stdio_usb.c