#include "bmp280.h"
#ifndef BMP280_IO
#define BMP280_IO
HAL_StatusTypeDef BMP280_read(unsigned char reg, unsigned char * buffer, unsigned short length);
HAL_StatusTypeDef BMP280_write(unsigned char reg, unsigned char * buffer, unsigned short length);
void BMP280_IO_I2C(I2C_HandleTypeDef * i);
#endif