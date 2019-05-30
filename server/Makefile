CC = g++
FLAGS = -Wall -lthrift
INC_DIR = include
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
INCLUDE = -I $(INC_DIR)

TARGET = server

OBJS = $(BUILD_DIR)/server.o $(BUILD_DIR)/PotdService.o \
	   $(BUILD_DIR)/potd_constants.o $(BUILD_DIR)/potd_types.o

$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CC) -o $@ $^ $(FLAGS) $(INCLUDE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@$(CC) -o $@ -c $^ $(FLAGS) $(INCLUDE)

run: $(BIN_DIR)/$(TARGET)
	@$(BIN_DIR)/$(TARGET)

clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

