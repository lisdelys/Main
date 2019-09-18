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



outdata CNT_IF(ap_uint<64> s_Compare, ap_uint<64> s_MASK, one s_CLR, one s_SET, one s_Load, ap_uint<64> s_Preload)
{
#pragma HLS INTERFACE s_axilite port=s_Preload bundle=M_Ctrl_Cntr
#pragma HLS INTERFACE s_axilite port=s_Load bundle=M_Ctrl_Cntr
#pragma HLS INTERFACE s_axilite port=s_SET bundle=M_Ctrl_Cntr
#pragma HLS INTERFACE s_axilite port=s_CLR bundle=M_Ctrl_Cntr
#pragma HLS INTERFACE s_axilite port=s_MASK bundle=M_Ctrl_Cntr
#pragma HLS INTERFACE s_axilite port=s_Compare bundle=M_Ctrl_Cntr
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS DATAFLOW

ap_uint<64>  temp1, temp2, tPre, hold;
outdata d;


//(s_Load == 1) ? (tPre = ((tPre)<<32)|(hold)) : (tPre = 0);

(s_Load == 1) ? (tPre = s_Preload) : (tPre = 0);

temp1 = tPre & s_MASK;
temp2 = s_Compare & s_MASK;


 d.Set = s_SET;
 d.Clr = s_CLR;
 d.Ld = s_Load;
 d.Preload = tPre;
 d.IR = (temp1 == temp2) ? 1:0; //true:false

 return d;
}


