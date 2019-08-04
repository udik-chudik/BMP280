# BMP280 HAL-based driver
## Description
This driver was written for BMP280 temperature and pressure transducer. Currently only I2C channel supported. Communication based on STM32 HAL driver, but another path could be added easily. Only one connected device supported.
Tests written using [UNITY]([google.com](https://www.throwtheswitch.org/unity)) test framework.
### Directory tree
* **build** - directory needed for autotests, can be ommited for production
* **inc** - directory with header files
* **src** - directory with source files
* **test** - directory with tests
## How to use with STM32CubeMX
Assuming *Makefile* toolchain.
1. Copy this repo into your **Drivers** directory in project folder.
2. Add **inc** directory and appropriate **.src** files into your *Makefile*:
```
-IDrivers/BMP280/inc
```
```
Drivers/BMP280/src/bmp280.c \
Drivers/BMP280/src/bmp280_i2c.c \
Drivers/BMP280/src/convertors.c
```
3. Include `bmp280.h` to your **main.c**:
```C
#include "bmp280.h"
```
4. Initialize driver with right **i2c** interface, for example:
```C
BMP280_Init(&i2c2);
```
5. Set device config, for example:
```C
bmp280_config conf;
conf.filter = FILTER_16;
conf.inactive = INACTIVE_125;
conf.mode = MODE_NORMAL;
conf.osrs_p = OVERSAMPLING_16;
conf.osrs_t = OVERSAMPLING_16;
BMP280_SetConfig(conf);
```
5. Finaly, acquire data:
```C
int32_t T = BMP280_GetTemperature();
uint64_t P = BMP280_GetPressure();
```
## Methods description
```C
int32_t BMP280_GetTemperature()
```
Returns temperature in T*100 deg Celcium. For example 2894 corresponds to 28.95 degrees.
```C
uint64_t BMP280_GetPressure()
```
Returns pressure in P*256 Pascal. For example 25600000 corresponds to 1000000 pascal.
```C
void BMP280_Init(I2C_HandleTypeDef * interface);
```
Initializes connection interface, loads calibration data. Assumes that I2C address is `0x76`
```C
void BMP280_Reset(void);
```
Gives chip id. For mass-production BMP280 id is `0x58`
```C
void BMP280_Reset(void);
```
Performs soft-reset of the chip.
```C
void BMP280_SetConfig(bmp280_config config);
```
Sets config. Detailed config description below.
## Config description
`bmp280_config` is a struct type with fields:
* inactive
* filter
* osrs_p
* osrs_t
* mode

You have to define all of this fields, because they do not have default values.
### `inactive`
Defines time interval (in ms) between measurments (data updates). Can take the following values:
* `INACTIVE_05`
* `INACTIVE_62_5`
* `INACTIVE_125`
* `INACTIVE_250`
* `INACTIVE_500`
* `INACTIVE_1000`
* `INACTIVE_2000`
* `INACTIVE_4000`

The number is interval in milliseconds. For example `INACTIVE_05` corresponds to 0.5ms, `INACTIVE_62_5` -> 62.5ms, `INACTIVE_2000` -> 2s.
### `filter`
Defines time-constant of internal FIR filter. Can take the folliwing values:
* `FILTER_OFF`
* `FILTER_2`
* `FILTER_4`
* `FILTER_8`
* `FILTER_16`

## `osrs_p` and `osrs_t`
Defines internal oversampling of measurments. Can take the folliwing values:
* `OVERSAMPLING_SKIPPED`
* `OVERSAMPLING_1`
* `OVERSAMPLING_2`
* `OVERSAMPLING_4`
* `OVERSAMPLING_8`
* `OVERSAMPLING_16`

## `mode`
Defines chip mode of operation. (Tested only with `MODE_NORMAL`). Can take the folliwing values:
* `MODE_SLEEP`
* `MODE_FORCED`
* `MODE_NORMAL`

## Known issues
Because compensation formula for *pressure* takes into account a temperature, for aciquire *precise pressure* you have to call `BMP280_GetTemperature()` first.

## Contribute
You can help this project by adding additional feature support, for example humidity measurments of BME280 or new communication chennels, porting to Arduino, etc. Make sure that tests passes:
```
make test


gcc -std=c99 -Wall -Wextra -Wpointer-arith -Wcast-align -Wwrite-strings -Wswitch-default -Wunreachable-code -Winit-self -Wmissing-field-initializers -Wno-unknown-pragmas -Wstrict-prototypes -Wundef -Wold-style-definition -g -Isrc -Itest/unity -Itest -Iinc -c test/unity/unity.c  test/i2c_fake.c src/bmp280.c src/convertors.c test/convertors_fake.c test/test_bmp280.c test/test_runners/bmp280_test_runner.c
mv *.o build/
gcc build/i2c_fake.o build/convertors_fake.o build/bmp280_test_runner.o build/test_bmp280.o build/unity.o build/bmp280.o  -o build/test1
build/test1
test/test_bmp280.c:40:test_Init_ShoulCallRead:PASS
test/test_bmp280.c:47:test_getCalibrationData:PASS
test/test_bmp280.c:67:test_getTemperature:PASS
test/test_bmp280.c:83:test_getPressure:PASS
test/test_bmp280.c:99:test_BMP280_Reset:PASS
test/test_bmp280.c:110:test_BMP280_SetConfig:PASS
test/test_bmp280.c:133:test_BMP280_GetChipId:PASS

-----------------------
7 Tests 0 Failures 0 Ignored 
OK
```