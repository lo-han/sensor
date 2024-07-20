# Compiler
CC = gcc
# Source directory
SRC_DIR = ./src
# Compiler flags
HEADERS_FOLDER=./headers
CORE_FOLDER=$(SRC_DIR)/core
TRIGGER_FOLDER=$(CORE_FOLDER)/trigger
SENSOR_FOLDER=$(CORE_FOLDER)/sensor
INCLUDE_FOLDER=./include
CFLAGS = -Wall -g -I $(INCLUDE_FOLDER) -I $(HEADERS_FOLDER)
# Object directory
OBJ_DIR = ./obj
# Source files
SRCS = $(TRIGGER_FOLDER)/trigger.c $(SENSOR_FOLDER)/sensor.c tests/mock/mock_sensor.c
# Object files
OBJS = $(patsubst %.c,%.o,$(SRCS))

# Default rule
all: $(OBJS)
	ld -r $(OBJS) -o $(OBJ_DIR)/sensor.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_DIR)/*.o
	@rm $(SRC_DIR)/*/*/*.o
	@rm tests/mock/*.o