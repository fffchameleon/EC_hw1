CXX = g++
CXXFLAGS = -std=c++17
SOURCES = main.cpp bga.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = main

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
