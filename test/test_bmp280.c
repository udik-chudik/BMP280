#include "unity.h"
#include "bmp280.h"
#include "i2c_fake.h"
#include "convertors_fake.h"

char i2c_read_was_called;
unsigned char i2c_read_param_reg;
unsigned char * i2c_read_param_buffer;
unsigned short i2c_read_param_length;

char i2c_write_was_called;
unsigned char i2c_write_param_reg;
unsigned char * i2c_write_param_buffer;
unsigned short i2c_write_param_length;

char compensate_T_was_called;
int compensate_T_arg;
char compensate_P_was_called;
int compensate_P_arg;


void setUp(void)
{
    i2c_read_was_called = 0;
    i2c_read_param_reg = 0;
    i2c_read_param_length = 0;
    i2c_read_param_buffer = NULL;

    i2c_write_was_called = 0;
    i2c_write_param_reg = 0;
    i2c_write_param_length = 0;
    i2c_write_param_buffer = NULL;

    compensate_T_was_called = 0;
    compensate_T_arg = 0;
    compensate_P_arg = 0;
    compensate_P_was_called = 0;
}

void test_Init_ShoulCallRead(void)
{
    BMP280_Init(NULL);
    TEST_ASSERT_MESSAGE(i2c_read_was_called == 1, "io/read() should have been called during initialization!");
    TEST_ASSERT_MESSAGE(i2c_read_param_reg == BMP280_REG_DIG_T1_LSB, "io/read() should have been called with BMP280_REG_DIG_T1_LSB register!");
}

void test_getCalibrationData(void)
{
    bmp280_calibration data = BMP280_GetCalibrationData();
    TEST_ASSERT_MESSAGE(i2c_read_was_called, "io/read() should have been called during initialization!");
    TEST_ASSERT_MESSAGE(i2c_read_param_reg == 0x88, "io/read() should have been called with BMP280_REG_DIG_T1_LSB register!");
    TEST_ASSERT_MESSAGE(i2c_read_param_length == 24, "io/read() should have been called for 24 registers!");
    TEST_ASSERT_EQUAL(0x0100, data.dig_T1);
    TEST_ASSERT_EQUAL(0x0302, data.dig_T2);
    TEST_ASSERT_EQUAL(0x0504, data.dig_T3);
    TEST_ASSERT_EQUAL(0x0706, data.dig_P1);
    TEST_ASSERT_EQUAL(0x0908, data.dig_P2);
    TEST_ASSERT_EQUAL(0x0b0a, data.dig_P3);
    TEST_ASSERT_EQUAL(0x0d0c, data.dig_P4);
    TEST_ASSERT_EQUAL(0x0f0e, data.dig_P5);
    TEST_ASSERT_EQUAL(0x1110, data.dig_P6);
    TEST_ASSERT_EQUAL(0x1312, data.dig_P7);
    TEST_ASSERT_EQUAL(0x1514, data.dig_P8);
    TEST_ASSERT_EQUAL(0x1716, data.dig_P9);
}

void test_getTemperature(void)
{
    //Try to get temperature
    int t = BMP280_GetTemperature();
    //Should read apropriate registers
    TEST_ASSERT_MESSAGE(i2c_read_was_called, "io/read() should have been called during getTemperature");
    TEST_ASSERT_EQUAL(3, i2c_read_param_length);
    TEST_ASSERT_EQUAL(0xfa, i2c_read_param_reg);
    //Should call converter
    TEST_ASSERT_MESSAGE(compensate_T_was_called, "BME280_compensate_T_int32 should have been called");
    //With apropriate data {0x00, 0x01, 0x02}
    TEST_ASSERT_EQUAL(0x000010, compensate_T_arg);
    //Test that getTemperature returns converted value
    TEST_ASSERT_EQUAL(-123, t);
}

void test_getPressure(void)
{
    //Try to get temperature
    unsigned int p = BMP280_GetPressure();
    //Should read apropriate registers
    TEST_ASSERT_MESSAGE(i2c_read_was_called, "io/read() should have been called during getPressure");
    TEST_ASSERT_EQUAL(3, i2c_read_param_length);
    TEST_ASSERT_EQUAL(0xf7, i2c_read_param_reg);
    //Should call converter
    TEST_ASSERT_MESSAGE(compensate_P_was_called, "BME280_compensate_P_int64 should have been called");
    //With apropriate data {0x00, 0x01, 0x00}
    TEST_ASSERT_EQUAL(0x000010, compensate_P_arg);
    //Test that getTemperature returns converted value
    TEST_ASSERT_EQUAL(123456, p);
}

void test_BMP280_Reset(void)
{
    BMP280_Reset();
    TEST_ASSERT_MESSAGE(i2c_write_was_called, "io/write() should have been called");
    TEST_ASSERT_EQUAL(0xb6, i2c_write_param_buffer[0]);
    TEST_ASSERT_EQUAL(1, i2c_write_param_length);
    TEST_ASSERT_EQUAL(0x0e, i2c_write_param_reg);
    //printf("%i\n\n\n", *i2c_write_param_buffer);
    
}

void test_BMP280_SetConfig(void)
{
    bmp280_config conf;
    conf.filter = FILTER_16;
    conf.inactive = INACTIVE_125;
    conf.mode = MODE_NORMAL;
    conf.osrs_p = OVERSAMPLING_16;
    conf.osrs_t = OVERSAMPLING_16;
    BMP280_SetConfig(conf);
    TEST_ASSERT_MESSAGE(i2c_write_was_called == 2, "io/write() should have been called twice during setting config");
    
    if (i2c_write_param_reg == 0xf4)
    {
        TEST_ASSERT_EQUAL(0b10010011, *i2c_write_param_buffer);
    }
    if (i2c_write_param_reg == 0xf5)
    {
        TEST_ASSERT_EQUAL(0b01010000, *i2c_write_param_buffer);
    }
    TEST_ASSERT_EQUAL(1, i2c_write_param_length);
    TEST_ASSERT_MESSAGE((i2c_write_param_reg == 0xf4 || i2c_write_param_reg == 0xf5), "io/write() during configuration should have been called with appropriate registers => 0xf4 or 0xf5");
}

void test_BMP280_GetChipId(void)
{
    uint8_t id = BMP280_GetChipId();
    TEST_ASSERT_MESSAGE(i2c_read_was_called, "io/read() should have been called once during reading chip id");
    TEST_ASSERT_EQUAL(1, i2c_read_param_length);
    TEST_ASSERT_EQUAL(0xd0, i2c_read_param_reg);
    TEST_ASSERT_EQUAL(0, id);
}