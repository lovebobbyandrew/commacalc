# Bobby Love
# December 17, 2021
# GNU GPL

PROGRAM := commacalc

SOURCES := $(wildcard *.cc)
HEADERS := $(wildcard *.h)
OBJS := $(SOURCES:.cc=.o)

CXXFLAGS := -std=c++11 -Wall -Werror

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: main.cc commacalc.h
commacalc.o: commacalc.cc commacalc.h

.PHONY: clean
clean:
	rm -f $(PROGRAM) $(OBJS)