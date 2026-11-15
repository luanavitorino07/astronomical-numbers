CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
TARGET = astronomicos
OBJ = main.o Lista.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

main.o: main.c Lista.h
	$(CC) $(CFLAGS) -c main.c

Lista.o: Lista.c Lista.h
	$(CC) $(CFLAGS) -c Lista.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all run clean
