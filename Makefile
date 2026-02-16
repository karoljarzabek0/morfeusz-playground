CXX = g++

CXXFLAGS = -Wall -Wextra  
CXXFLAGS += -I external/morfeusz/include
CXXFLAGS += -L external/morfeusz/lib
CXXFLAGS += -l morfeusz2

main: src/main.cpp
	$(CXX) $< -o build/main $(CXXFLAGS)

clean:
	rm -f main