#include "convertors.h"

bmp280_calibration BMP280_CALIBRATION_DATA;

BME280_S32_t t_fine;
BME280_S32_t BME280_compensate_T_int32(BME280_S32_t adc_T)
{
    BME280_S32_t var1, var2, T;
    var1 = ((((adc_T>>3) - ((BME280_S32_t)BMP280_CALIBRATION_DATA.dig_T1<<1))) * ((BME280_S32_t)BMP280_CALIBRATION_DATA.dig_T2)) >> 11;
    var2 = (((((adc_T>>4) - ((BME280_S32_t)BMP280_CALIBRATION_DATA.dig_T1)) * ((adc_T>>4) - ((BME280_S32_t)BMP280_CALIBRATION_DATA.dig_T1))) >> 12) * ((BME280_S32_t)BMP280_CALIBRATION_DATA.dig_T3)) >> 14;
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}

BME280_U32_t BME280_compensate_P_int64(BME280_S32_t adc_P)
{
    BME280_S64_t var1, var2, p;
    var1 = ((BME280_S64_t)t_fine) - 128000;
    var2 = var1 * var1 * (BME280_S64_t)BMP280_CALIBRATION_DATA.dig_P6;
    var2 = var2 + ((var1*(BME280_S64_t)BMP280_CALIBRATION_DATA.dig_P5)<<17);
    var2 = var2 + (((BME280_S64_t)BMP280_CALIBRATION_DATA.dig_P4)<<35);
    var1 = ((var1 * var1 * (BME280_S64_t)BMP280_CALIBRATION_DATA.dig_P3)>>8) + ((var1 * (BME280_S64_t)BMP280_CALIBRATION_DATA.dig_P2)<<12);
    var1 = (((((BME280_S64_t)1)<<47)+var1))*((BME280_S64_t)BMP280_CALIBRATION_DATA.dig_P1)>>33;
    if (var1 == 0)
    {
        return 0;
    }
    p = 1048576-adc_P;
    p = (((p<<31)-var2)*3125)/var1;
    var1 = (((BME280_S64_t)BMP280_CALIBRATION_DATA.dig_P9) * (p>>13) * (p>>13)) >> 25;
    var2 = (((BME280_S64_t)BMP280_CALIBRATION_DATA.dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((BME280_S64_t)BMP280_CALIBRATION_DATA.dig_P7)<<4);
    return (BME280_U32_t)p;
}