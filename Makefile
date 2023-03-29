CXX = g++
CXXFLAGS=-std=c++17 -Wall -O2 -fsanitize=address -g

SRC_DIR = src
INCLUDE_DIR = include
PLOT_DIR = plot

SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/bga.cpp $(SRC_DIR)/rga.cpp $(SRC_DIR)/global.cpp 

EXECUTABLE = ./main
OBJS = main

.PHONY: all
all: $(OBJS)

main: $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: run
run: all
	./main $(ARGS)

plot:
	python3 $(PLOT_DIR)/plot.py

result: all run plot 

clean:
	rm $(EXECUTABLE)
