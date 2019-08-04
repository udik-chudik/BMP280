#include "bmp280_io.h"
#include "i2c.h"
I2C_HandleTypeDef * interface;

void BMP280_IO_I2C(I2C_HandleTypeDef * i)
{
    interface = i;
}

HAL_StatusTypeDef BMP280_read(unsigned char reg, unsigned char *buffer, unsigned short length)
{
    return HAL_I2C_Mem_Read(interface, 0x76<<1, reg, 1, buffer, length, 10);
}

HAL_StatusTypeDef BMP280_write(unsigned char reg, unsigned char *buffer, unsigned short length)
{
    return HAL_I2C_Mem_Write(interface, 0x76<<1, reg, 1, buffer, length, 10);
}