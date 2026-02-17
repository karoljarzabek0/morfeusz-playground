CXX = g++

CXXFLAGS = -Wall -Wextra  
CXXFLAGS += -I external/morfeusz/include
CXXFLAGS += -L external/morfeusz/lib
CXXFLAGS += -l morfeusz2

main: src/main.cpp
	$(CXX) $< -o build/main $(CXXFLAGS)


pdf: src/pdf.cpp
	$(CXX) $< -o build/pdf $(CXXFLAGS)

.PHONY: clean
clean:
	del .\build\main.exe

