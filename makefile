CCC = gcc
CCFLAGS = -g -Wall -Iinclude

SOURCE = $(wildcard src/*.c)
INCLUDE = $(wildcard ./include/*.h)
OBJECTS = $(SOURCE:./src/%.c=./bin/%.o) bin/trab2.o

TARGET = trab2

all: $(TARGET)

$(TARGET): $(OBJECTS) 
	$(CCC) $(CCFLAGS) -o $@ $^ 

bin/%.o: ./src/%.c $(INCLUDE) | bin
	$(CCC) $(CCFLAGS) -c -o $@ $<

bin/trab2.o: trab2.c $(INCLUDE) | bin
	$(CCC) $(CCFLAGS) -c -o $@ $< 

clean:
	rm -f bin/*.o $(TARGET)
