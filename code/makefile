OBJECTS = main.o
INC = -Wall -I/usr/local/include
GSLLIBS = -L/usr/local/lib -lm -lgsl -lgslcblas 
BOOSTLIBS = -I/usr/local/include/boost/ -lboost_filesystem -lboost_system -lboost_timer
CC = g++

all: main

%.o:    src/%.cpp
	$(CC) -c $(INC) $< -o $@

main: $(OBJECTS)
	$(CC) $(OBJECTS) $(GSLLIBS) $(BOOSTLIBS) -o $@

clean:
	-rm -f $(OBJECTS) main

