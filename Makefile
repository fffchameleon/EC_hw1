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
#	./main $(ARGS)
#	./main
	for p in $$(seq 2 3 11); do \
		time ./main --p_select $$p; \
	done

#	for p in $$(seq 100 300 1000); do \
		time ./main --p_size $$p; \
	done

#	for p in $$(seq 0.1 0.3 1); do \
		time ./main --cross_prob $$p; \
	done

#	for p in $$(seq 0.1 0.3 1); do \
	 	time ./main --mut_prob $$p; \
	done

#	for p in $$(seq 0 1 1); do \
		time ./main --uniform $$p; \
	done

#	for p in $$(seq 500 300 1100); do \
		time ./main --term $$p; \
	done	

	for p in $$(seq 2 1 9); do \
		time ./main --n_point $$p --algorithm binary; \
	done
	
.PHONY: plot
plot:
	python3 $(PLOT_DIR)/plot.py

result: all run plot 

clean:
	rm $(EXECUTABLE) && rm -r ./data/*
