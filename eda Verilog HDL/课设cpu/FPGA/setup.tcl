set_global_assignment -name FAMILY "Cyclone III"
set_global_assignment -name DEVICE EP3C55F484C8
set_global_assignment -name RESERVE_ALL_UNUSED_PINS "AS INPUT TRI-STATED"
set_global_assignment -name RESERVE_ALL_UNUSED_PINS_NO_OUTPUT_GND "AS INPUT TRI-STATED"
# system clock and reset
set_location_assignment PIN_T2    -to CLK
set_location_assignment PIN_B11   -to Rstn
# led
#set_location_assignment PIN_F13   -to led0
#set_location_assignment PIN_D10   -to led1
# uart
set_location_assignment PIN_E21   -to RXD
set_location_assignment PIN_E22   -to TXD

