UNITY_ROOT=test/unity

CFLAGS=-std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition
CFLAGS += -g

INC_DIRS=-Isrc -I$(UNITY_ROOT) -Itest -Iinc

SRC_FILES1=$(UNITY_ROOT)/unity.c  test/i2c_fake.c src/bmp280.c src/convertors.c test/convertors_fake.c test/test_bmp280.c test/test_runners/bmp280_test_runner.c
TEST_TARGET1=test1

objects: $(SRC_FILES1)
	gcc $(CFLAGS) $(INC_DIRS) -c $(SRC_FILES1)
	mv *.o build/

default: objects
	gcc build/i2c_fake.o build/convertors_fake.o build/bmp280_test_runner.o build/test_bmp280.o build/unity.o build/bmp280.o  -o build/$(TEST_TARGET1)

test/test_runners/bmp280_test_runner.c: test/test_bmp280.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_bmp280.c test/test_runners/bmp280_test_runner.c

test: default
	build/${TEST_TARGET1}

clean:
	rm -rf build/*