#include <stdio.h>
#include <stdint.h>

union union_change
{
    
    uint8_t i_array[4];
    uint32_t i_32;
    float    f;
};

int main(void)
{
	union union_change array1, array2, array3;
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