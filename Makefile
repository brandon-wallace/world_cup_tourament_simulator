CXX = g++
# CXXFLAGS = -Wall -Weffc++ -Wextra -Wsign-conversion -Werror -pipe -O2 -DNDEBUG 
CXXFLAGS = -std=c++17 -Wall -Weffc++ -Wextra -Werror -pipe -O2 -DNDEBUG 
LDLIBS = 
RM = rm -f

all: main

debug: CXXFLAGS += -ggdb 
debug: main

main:
	$(CXX) $(CXXFLAGS) -o main io.cpp main.cpp 


clean:
	$(RM) main
