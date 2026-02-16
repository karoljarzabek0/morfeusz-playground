CXX = g++

CXXFLAGS = -Wall -Wextra -I include -L lib -l morfeusz2 -Wl,-rpath,'$$ORIGIN/lib'

main: main.cpp
	$(CXX) main.cpp -o main $(CXXFLAGS)

clean:
	rm -f main