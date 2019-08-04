#include "convertors_fake.h"

char compensate_T_was_called;
int compensate_T_arg;

char compensate_P_was_called;
int compensate_P_arg;

int BME280_compensate_T_int32(int adc)
{
    compensate_T_was_called = 1;
    compensate_T_arg = adc;
    return -123;
}

unsigned int BME280_compensate_P_int64(int adc)
{
    compensate_P_was_called = 1;
    compensate_P_arg = adc;
    return 123456;
}