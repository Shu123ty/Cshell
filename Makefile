
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

TARGET = CSHELL
SOURCES = main.cpp $(wildcard src/*.cpp)

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
