#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../include/Crc16.h"

union union_change
{
    
    uint8_t i_array[4];
    uint32_t i_32;
    float    f;
};

int main(void)
{
	union union_change array1, array2, array3;
	char *test = (char *)malloc(sizeof(char) * 29);
	test[0] = 0x70;
	test[1] = 0x03;
	test[2] = 0x18;
	test[3] = 0x6F;
	test[4] = 0xA4;
	test[5] = 0xBF;
	test[6] = 0x3F;
	test[7] = 0x6E;
	test[8] = 0x4B;
	test[9] = 0xBE;
	test[10] = 0x3F;
	test[11] = 0xD2;
	test[12] = 0x03;
	test[13] = 0xEA;
	test[14] =0x3F;
	test[15] = 0x5A;
	test[16] = 0x0D;
	test[17] = 0x23;
	test[18] = 0x40;
	test[19] = 0x7A;
	test[20] = 0xA6;
	test[21] = 0x1F;
	test[22] = 0x40;
	test[23] = 0x4F;
	test[24] = 0xDC;
	test[25] = 0xA2;
	test[26] = 0x3F;
	test[27] = 0x21;
	test[28] = 0xF3;

	short test_int;
	test_int = calc_crc16(test, 29);
	printf("666\n%d\n", test_int);
	array1.i_array[0] = 0x6f;
	array1.i_array[1] = 0xa4;
	array1.i_array[2] = 0xbf;
	array1.i_array[3] = 0x3f;

	array2.i_array[0] = 0x6e;
	array2.i_array[1] = 0x4b;
	array2.i_array[2] = 0xbe;
	array2.i_array[3] = 0x3f;

	array3.i_array[0] = 0xd2;
	array3.i_array[1] = 0x03;
	array3.i_array[2] = 0xea;
	array3.i_array[3] = 0x3f;


	printf("%f\n%x\n%f\n%x\n%f\n%x\n", array1.f, array1.i_32, array2.f, array2.i_32, array3.f, array3.i_32);
	return 0;
}