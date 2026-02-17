CXX = g++

CXXFLAGS = -Wall -Wextra  
CXXFLAGS += -I external/morfeusz/include
CXXFLAGS += -L external/morfeusz/lib
CXXFLAGS += -l morfeusz2
MAINCXXFLAGS = -I src

SRCS = $(wildcard src/*.cpp)

main: $(SRCS)
	$(CXX) $(SRCS) -o build/main $(CXXFLAGS) $(MAINCXXFLAGS)

test_pdf: src/pdf.cpp
	$(CXX) src/pdf.cpp -o build/test_pdf $(CXXFLAGS) -D DEBUG

.PHONY: clean
clean:
	del .\build\main.exe

