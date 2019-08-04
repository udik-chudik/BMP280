#include "i2c_fake.h"
#include <stdio.h>
char i2c_read_was_called;
unsigned char i2c_read_param_reg;
unsigned char * i2c_read_param_buffer;
unsigned short i2c_read_param_length;

char i2c_write_was_called;
unsigned char i2c_write_param_reg;
unsigned char * i2c_write_param_buffer;
unsigned short i2c_write_param_length;

I2C_HandleTypeDef * interface;

void BMP280_IO_I2C(I2C_HandleTypeDef * i)
{
    interface = i;
}

int BMP280_read(unsigned char reg, unsigned char *buffer, unsigned short length)
{
    i2c_read_was_called++;
    i2c_read_param_reg = reg;
    i2c_read_param_buffer = buffer;
    i2c_read_param_length = length;
    for (int i = 0; i < length; i++)
    {
        buffer[i] = i;
    }
    return 300;
}

int BMP280_write(unsigned char reg, unsigned char *buffer, unsigned short length)
{
    i2c_write_was_called++;
    i2c_write_param_reg = reg;
    i2c_write_param_buffer = &(*buffer);
    i2c_write_param_length = length;
    //printf("%x\n\n\n", *i2c_write_param_buffer);
    return 400;
}