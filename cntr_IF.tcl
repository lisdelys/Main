############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project -reset Counter_Interface_1
set_top CNT_IF
add_files cntr_IF.cpp
add_files -tb cntr_IF_Test.cpp -cflags "-Wno-unknown-pragmas"

#Solution
open_solution -reset "solution1"
set_part {xczu9eg-ffvb1156-2-i} -tool vivado
create_clock -period 10 -name default

#source "directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog

exit
