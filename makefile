# Compiler and compiler flags
CC := gcc
CFLAGS := -Wall -Wextra -Iinclude

# Source and build directories
SRC_DIR := src
BIN_DIR := ./bin

# Create subdirectories for object files
$(shell mkdir -p $(BIN_DIR))

# Source files and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Executable names
SERVER_EXEC := $(BIN_DIR)/server
CLIENT_EXEC := $(BIN_DIR)/client

# Phony targets
.PHONY: all clean

# Default target
all: $(SERVER_EXEC) $(CLIENT_EXEC)

# Build server executable
$(SERVER_EXEC): $(BIN_DIR)/server.o $(BIN_DIR)/utils.o
	$(CC) $(CFLAGS) $^ -o $@

# Build client executable
$(CLIENT_EXEC): $(BIN_DIR)/client.o $(BIN_DIR)/utils.o
	$(CC) $(CFLAGS) $^ -o $@

# Compile source files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c include/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the generated files
clean:
	rm -f $(OBJS) $(SERVER_EXEC) $(CLIENT_EXEC)
