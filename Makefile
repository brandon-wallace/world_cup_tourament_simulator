CXX = g++
CXXFLAGS = -std=c++17 -Wall -Weffc++ -Wextra -Werror -Wshadow -pipe -O2 -DNDEBUG
LDLIBS = 
RM = rm -f

all: main

debug: CXXFLAGS += -ggdb 
debug: main

main:
	$(CXX) $(CXXFLAGS) -o main io.cpp main.cpp 


clean:
	$(RM) main
