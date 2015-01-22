OBJECTS = main.o
INC = -Wall -I/usr/local/include
LIBS = -L/usr/local/lib -lm -lgsl -lgslcblas
CC = g++ 

all: main

%.o:    src/%.cpp
	$(CC) -c $(INC) $< -o $@

main: $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

clean:
	-rm -f $(OBJECTS) main