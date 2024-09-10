CCC = gcc
CCFLAGS = -Iinclude

SOURCE = $(wildcard src/*.c)
INCLUDE = $(wildcard ./include/*.h)
OBJECTS = $(SOURCE:.c=.o) trab2.o

TARGET = trab2

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CCC) $(CCFLAGS) -o $@ $^

%.o: %.c $(INCLUDE)
	$(CCC) $(CCFLAGS) -c -o $@ $<

trab2.o: trab2.c $(INCLUDE)
	$(CCC) $(CCFLAGS) -c -o $@ $< 

clean:
	rm -f src/*.o trab2.o $(TARGET)
