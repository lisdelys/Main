#include <hls_stream.h>
#include <ap_int.h>
#include <stdio.h>

//typedef ap_int<1>  one;
typedef bool one;


struct outdata {
	one Clr;
	one Set;
	one Ld;
	ap_uint<64>  Preload;
	one IR;
};

outdata mytest, gold;

void goldinput (one s_CLR, one s_SET, one s_Load, ap_uint<64>  Preload, one IR ){

		gold.Clr =s_CLR;
		gold.Set= s_SET;
		gold.Ld = s_Load;
		gold.Preload= Preload;
		gold.IR = IR;

}

outdata CNT_IF(ap_uint<64> s_Compare, ap_uint<64> s_MASK, one s_CLR, one s_SET, one s_Load, ap_uint<32> s_Preload_H, ap_uint<32> s_Preload_L);

bool comp(outdata in1, outdata in2){
	if ( in1.Preload == in2.Preload &&
			in1.Set == in2.Set &&
			in1.Clr == in2.Clr &&
			in1.Ld == in2.Ld &&
			in1.IR == in2.IR
			){printf("true \n");return true;}
	else {printf("false \n");
				return false;}
}

int main (){


	mytest = CNT_IF(0xAAAA111133334444, 0xFFFF000000000000,0,1,1,0xAAAACCCC, 0xBBBBFFFF);
	goldinput(0,1,1,0xAAAACCCCBBBBFFFF,1);
	comp(mytest, gold);


	mytest = CNT_IF(0xAAAA111133334444, 0x55550000FFFF0000,0,0,0,32,17);
	goldinput(0,0,0,0,0);
	comp(mytest, gold);

	mytest = CNT_IF(0xAAAA1111BBBB4444, 0x0000000000000000, 1,0,1,0xA321C58C, 0xBBBBFFFF);
	goldinput(1,0,1,0xA321C58CBBBBFFFF,1);
	comp(mytest, gold);

	mytest = CNT_IF(0xAAAA1111BBBB0001, 0x000000000000FFFF, 1,0,1,0xA321C58C, 0xBBBB0001);
	goldinput(1,0,1,0xA321C58CBBBB0001,1);
	comp(mytest, gold);



	return 0;
}
