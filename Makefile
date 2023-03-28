CXX = g++
CXXFLAGS = -std=c++17

SRC_DIR = src
INCLUDE_DIR = include
DATA_DIR = data
BUILD_DIR = build
PLOT_DIR = plot

SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/bga.cpp $(SRC_DIR)/rga.cpp $(SRC_DIR)/global.cpp
OBJ_FILES = $(BUILD_DIR)/main.o $(BUILD_DIR)/bga.o $(BUILD_DIR)/rga.o $(BUILD_DIR)/global.o

EXECUTABLE = $(BUILD_DIR)/main

.PHONY: all plot clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

run: $(EXECUTABLE)
	./$(EXECUTABLE) && mv fitness.csv $(DATA_DIR)/fitness.csv

plot:
	python3 $(PLOT_DIR)/plot.py

clean:
	rm -f $(BUILD_DIR)/*.o $(EXECUTABLE)
