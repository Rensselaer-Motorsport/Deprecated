# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Eric\Documents\GitHub\Corner-Module\CornerModule\CornerModule.cydsn\CornerModule.cyprj
# Date: Wed, 25 Mar 2015 21:25:46 GMT
#set_units -time ns
create_clock -name {I2C_1_SCBCLK(FFB)} -period 625 -waveform {0 312.5} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {CyHFCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_generated_clock -name {I2C_1_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 15 31} [list]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CySYSCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]


# Component constraints for C:\Users\Eric\Documents\GitHub\Corner-Module\CornerModule\CornerModule.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Eric\Documents\GitHub\Corner-Module\CornerModule\CornerModule.cydsn\CornerModule.cyprj
# Date: Wed, 25 Mar 2015 21:25:43 GMT
