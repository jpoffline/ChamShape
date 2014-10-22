OBJECTS = main.o
INC = -Wall -I/usr/local/include

CC = g++ -std=c++0x

all: main

%.o:    src/%.cpp
	$(CC) -c $(INC) $< -o $@

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS) main

