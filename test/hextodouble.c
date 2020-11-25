#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/config.h"

union test1_T
{
    uint8_t byte[8];
    double num;
}test1_t;

union test2_T
{
    uint8_t byte[4];
    float num;
}test2_t;

union test3_T
{
    uint8_t byte[4];
    int num;
}test3_t;

union test4_T
{
    uint8_t byte[2];
    short num;
}test4_t;


int main(void)
{
    union test1_T test1;
    union test2_T test2;
    union test3_T test3;
    union test4_T test4;
    test1.byte[0] = 0x29;
    test1.byte[1] = 0x3c;
    test1.byte[2] = 0x7c;
    test1.byte[3] = 0x13;
    test1.byte[4] = 0x42;
    test1.byte[5] = 0xef;
    test1.byte[6] = 0xd7;
    test1.byte[7] = 0x41;

    test2.byte[0] = 0x00;
    test2.byte[1] = 0x4d;
    test2.byte[2] = 0x1e;
    test2.byte[3] = 0xbf;

    test3.num = 200;

    test4.num = SIMPLE_RATE;

    printf("%x %x %x %x\n", test3.byte[0], test3.byte[1], test3.byte[2], test3.byte[3]);
    printf("%f\n%.20f\n", test1.num, test2.num);
    printf("%x %x\n", test4.byte[0], test4.byte[1]);
    return 0;
}