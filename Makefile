
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
TARGET = main
OBJS = main.o Lista.o

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c Lista.h
	$(CC) $(CFLAGS) -c main.c

Lista.o: Lista.c Lista.h
	$(CC) $(CFLAGS) -c Lista.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
