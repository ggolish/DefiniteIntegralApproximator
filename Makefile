CC = gcc
CFLAGS = -Wall -g
OBJS = scanner.o main.o simpson.o parser.o
TARGET = integrate

default: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c

scanner.o: scanner.c scanner.h

simpson.o: simpson.c simpson.h

parser.o: parser.c parser.h

clean:
	rm -f $(OBJS) $(TARGET)
