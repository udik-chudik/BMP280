#include "bmp280.h"
#ifndef BMP280_CONVERTORS
#define BMP280_CONVERTORS

#define BME280_S32_t int32_t
#define BME280_U32_t uint32_t
#define BME280_S64_t int64_t

extern bmp280_calibration BMP280_CALIBRATION_DATA;

BME280_S32_t BME280_compensate_T_int32(BME280_S32_t adc_T);
BME280_U32_t BME280_compensate_P_int64(BME280_S32_t adc_P);
#endif