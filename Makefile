CC=g++
TARGET_EXEC=main

BUILD_DIR=./build

INC_DIR=./include 
OBJ_DIR=./obj
SRC_DIR=./src

SRCS=$(wildcard $(SRC_DIR)/*.c) 
OBJS=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
INC_FLAGS = $(addprefix -I,$(INC_DIR))

CFLAGS=$(INC_FLAGS) 
CFLAGS += -std=c17
CFLAGS += -g
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


$(OBJ_DIR)/ltc2943.o: $(SRC_DIR)/ltc2943.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ltc2943.c -o $(OBJ_DIR)/ltc2943.o

$(OBJ_DIR)/i2c_driver.o: $(SRC_DIR)/i2c_driver.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/i2c_driver.c -o $(OBJ_DIR)/i2c_driver.o

$(OBJ_DIR):
	mkdir $@
