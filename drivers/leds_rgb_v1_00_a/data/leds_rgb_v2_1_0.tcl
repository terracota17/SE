##############################################################################
## Filename:          C:\Users\CJRipa\Pictures\Proyecto\PracticasSE/drivers/leds_rgb_v1_00_a/data/leds_rgb_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Tue Jan 31 18:48:48 2023 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "leds_rgb" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
