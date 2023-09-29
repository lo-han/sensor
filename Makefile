CC=gcc

CORE_FOLDER=./core
INFRA_FOLDER=./infra
DEPLOY_FOLDER=./deploy

TRIGGER_FOLDER=$(CORE_FOLDER)/trigger
MEMORY_FOLDER=$(CORE_FOLDER)/memory
SENSOR_FOLDER=$(CORE_FOLDER)/sensor

MOCK_WAIT_INFRA_FOLDER=$(INFRA_FOLDER)/mock
MOCK_MAIN_FOLDER=$(DEPLOY_FOLDER)/mock

CFLAGS=-I $(TRIGGER_FOLDER) -I $(MEMORY_FOLDER) -I $(SENSOR_FOLDER)

sensor_mock: $(TRIGGER_FOLDER)/trigger.c $(MEMORY_FOLDER)/safe_memory.c $(SENSOR_FOLDER)/sensor.c $(MOCK_WAIT_INFRA_FOLDER)/mock_sensor.c $(MOCK_MAIN_FOLDER)/main.c
	@$(CC) -o sensor_mock $(CFLAGS) $(TRIGGER_FOLDER)/trigger.c $(MEMORY_FOLDER)/safe_memory.c $(SENSOR_FOLDER)/sensor.c $(MOCK_WAIT_INFRA_FOLDER)/mock_sensor.c $(MOCK_MAIN_FOLDER)/main.c

clean:
	@rm echo_lib sensor_mock
