CC=gcc

HEADERS_FOLDER=../headers
CORE_FOLDER=../src/core
TRIGGER_FOLDER=$(CORE_FOLDER)/trigger
SENSOR_FOLDER=$(CORE_FOLDER)/sensor
MOCK_FOLDER=./mock
LIB_FOLDER=../lib
INCLUDE_FOLDER=../include

CFLAGS=-I $(HEADERS_FOLDER) -I $(INCLUDE_FOLDER)

sensor_mock: $(TRIGGER_FOLDER)/trigger.c $(SENSOR_FOLDER)/sensor.c $(MOCK_FOLDER)/mock_sensor.c $(MOCK_FOLDER)/main.c
	@$(CC) -o sensor_mock $(CFLAGS) $(TRIGGER_FOLDER)/trigger.c $(LIB_FOLDER)/safe_memory.o $(SENSOR_FOLDER)/sensor.c $(MOCK_FOLDER)/mock_sensor.c $(MOCK_FOLDER)/main.c

clean:
	@rm sensor_mock
