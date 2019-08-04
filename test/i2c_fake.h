#include "bmp280_io.h"
#define I2C_HandleTypeDef int
#define HAL_StatusTypeDef int
extern char i2c_read_was_called;
extern unsigned char i2c_read_param_reg;
extern unsigned char * i2c_read_param_buffer;
extern unsigned short i2c_read_param_length;

extern char i2c_write_was_called;
extern unsigned char i2c_write_param_reg;
extern unsigned char * i2c_write_param_buffer;
extern unsigned short i2c_write_param_length;