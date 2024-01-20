CXX = g++
FLAGS = -std=c++20 -Wall
LIBS = -lm -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf
SRC = $(wildcard src/*.cpp)
TARGET = main

.SILENT:
.PHONY: all run clean

all: $(TARGET)

$(TARGET): main.cpp $(SRC)
	$(CXX) $(FLAGS) -o $@ $^ $(LIBS)

run: all
	./main

clean:
	$(RM) $(TARGET)