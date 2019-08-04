/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Test Runner Used To Run Each Test Below=====*/
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  UNITY_EXEC_TIME_START(); \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT()) \
  { \
    tearDown(); \
  } \
  UNITY_EXEC_TIME_STOP(); \
  UnityConcludeTest(); \
}

/*=======Automagically Detected Files To Include=====*/
#define UNITY_INCLUDE_SETUP_STUBS
#include "unity.h"
#ifndef UNITY_EXCLUDE_SETJMP_H
#include <setjmp.h>
#endif
#include <stdio.h>
#include "bmp280.h"
#include "i2c_fake.h"
#include "convertors_fake.h"

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_Init_ShoulCallRead(void);
extern void test_getCalibrationData(void);
extern void test_getTemperature(void);
extern void test_getPressure(void);
extern void test_BMP280_Reset(void);
extern void test_BMP280_SetConfig(void);
extern void test_BMP280_GetChipId(void);


/*=======Suite Setup=====*/
static void suite_setup(void)
{
#if defined(UNITY_WEAK_ATTRIBUTE) || defined(UNITY_WEAK_PRAGMA)
  suiteSetUp();
#endif
}

/*=======Suite Teardown=====*/
static int suite_teardown(int num_failures)
{
#if defined(UNITY_WEAK_ATTRIBUTE) || defined(UNITY_WEAK_PRAGMA)
  return suiteTearDown(num_failures);
#else
  return num_failures;
#endif
}

/*=======Test Reset Option=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  setUp();
}


/*=======MAIN=====*/
int main(void)
{
  suite_setup();
  UnityBegin("test/test_bmp280.c");
  RUN_TEST(test_Init_ShoulCallRead, 40);
  RUN_TEST(test_getCalibrationData, 47);
  RUN_TEST(test_getTemperature, 67);
  RUN_TEST(test_getPressure, 83);
  RUN_TEST(test_BMP280_Reset, 99);
  RUN_TEST(test_BMP280_SetConfig, 110);
  RUN_TEST(test_BMP280_GetChipId, 133);

  return suite_teardown(UnityEnd());
}