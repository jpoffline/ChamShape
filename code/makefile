OBJECTS = main.o
INC = -Wall -I/usr/local/include

CC = g++

all: main

%.o:    src/%.cpp
	$(CC) -c $(INC) $< -o $@

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS) main

