#include <hls_stream.h>
#include <ap_int.h>
#include <stdio.h>
#include <iostream>

//typedef ap_int<1>  one;
typedef bool one;

struct outdata {
	one Clr;
	one Set;
	one Ld;
	ap_uint<64>  Preload;
	one IR;
};



outdata CNT_IF(ap_uint<64> s_Compare, ap_uint<64> s_MASK, one s_CLR, one s_SET, one s_Load, ap_uint<32> s_Preload_H, ap_uint<32> s_Preload_L)
{
#pragma HLS DATAFLOW
#pragma HLS INTERFACE s_axilite port=s_Preload_L bundle=L
#pragma HLS INTERFACE s_axilite port=s_Preload_H bundle=H
#pragma HLS INTERFACE ap_ctrl_none port=return

ap_uint<64>  temp1, temp2, tPre, hold;
outdata d;

tPre = s_Preload_H;
hold = s_Preload_L;
(s_Load == 1) ? (tPre = ((tPre)<<32)|(hold)) : (tPre = 0);


temp1 = tPre & s_MASK;
temp2 = s_Compare & s_MASK;


 d.Set = s_SET;
 d.Clr = s_CLR;
 d.Ld = s_Load;
 d.Preload = tPre;
 d.IR = (temp1 == temp2) ? 1:0; //true:false

 return d;
}


