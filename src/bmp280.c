#include "bmp280.h"
#include "bmp280_io.h"
#include "convertors.h"

bmp280_calibration BMP280_CALIBRATION_DATA;

bmp280_calibration BMP280_GetCalibrationData(void)
{
    bmp280_calibration calibration_data;
    uint8_t data[24];
    BMP280_read(BMP280_REG_DIG_T1_LSB, data, sizeof(data));
    calibration_data.dig_T1 = (uint16_t)*(uint16_t *)&data[0];
    calibration_data.dig_T2 = (int16_t)*(int16_t *)&data[2];
    calibration_data.dig_T3 = (int16_t)*(int16_t *)&data[4];
    calibration_data.dig_P1 = (uint16_t)*(uint16_t *)&data[6];
    calibration_data.dig_P2 = (int16_t)*(int16_t *)&data[8];
    calibration_data.dig_P3 = (int16_t)*(int16_t *)&data[10];
    calibration_data.dig_P4 = (int16_t)*(int16_t *)&data[12];
    calibration_data.dig_P5 = (int16_t)*(int16_t *)&data[14];
    calibration_data.dig_P6 = (int16_t)*(int16_t *)&data[16];
    calibration_data.dig_P7 = (int16_t)*(int16_t *)&data[18];
    calibration_data.dig_P8 = (int16_t)*(int16_t *)&data[20];
    calibration_data.dig_P9 = (int16_t)*(int16_t *)&data[22];
    return calibration_data;
}

uint8_t BMP280_GetChipId(void)
{
    uint8_t data[1];
    BMP280_read(BMP280_REG_CHIP_ID, data, 1);
    return data[0];
}

int32_t BMP280_GetTemperature(void)
{
    uint8_t data[3];
    BMP280_read(BMP280_REG_TEMPERATURE, data, sizeof(data));
    int adc = (int32_t) ((((int32_t) (data[0])) << 12) | (((int32_t) (data[1])) << 4) | (((int32_t) (data[2])) >> 4));
    return BME280_compensate_T_int32(adc);
}

uint64_t BMP280_GetPressure(void)
{
    uint8_t data[3];
    BMP280_read(BMP280_REG_PRESSURE, data, sizeof(data));
    int adc = (int32_t) ((((int32_t) (data[0])) << 12) | (((int32_t) (data[1])) << 4) | (((int32_t) (data[2])) >> 4));
    return BME280_compensate_P_int64(adc);
}

void BMP280_Reset(void)
{
    uint8_t data = BMP280_RESET_VALUE;
    BMP280_write(BMP280_REG_RESET, &data, 1);
}

void BMP280_SetConfig(bmp280_config conf)
{
    uint8_t config_reg = ((uint8_t) (conf.inactive<<5)) | ((uint8_t) (conf.filter << 2));
    uint8_t ctrl_reg = ((uint8_t) (conf.osrs_p << 5)) | ((uint8_t) (conf.osrs_t << 2)) | ((uint8_t) conf.mode & 0b00000011);
    BMP280_write(BMP280_REG_CTRL_MEAS, &ctrl_reg, 1);
    BMP280_write(BMP280_REG_CONFIG, &config_reg, 1);
}

void BMP280_Init(I2C_HandleTypeDef * i)
{
    BMP280_IO_I2C(i);
    BMP280_CALIBRATION_DATA = BMP280_GetCalibrationData();
}
