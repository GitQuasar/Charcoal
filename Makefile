CC := clang++
CFLAGS := -std=c++17 -Wall

SRC_DIR := src
INCLUDE_DIR := include
BIN_DIR := bin
LIB_DIR := lib

LIBRARIES := -lpdcurses
EXECUTABLE := Charcoal.exe

build: $(SRC_DIR)/*.cpp
	$(info Building...)
	$(CC) $(CFLAGS) -g $(SRC_DIR)/*.cpp -I$(INCLUDE_DIR) -L$(LIB_DIR) $(LIBRARIES) -o $(BIN_DIR)/$(EXECUTABLE)