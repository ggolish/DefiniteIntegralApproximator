CC = gcc
CFLAGS = -Wall -g
CLIBS = -lm
OBJS = scanner.o main.o simpson.o parser.o stqu.o ast.o
TARGET = integrate

default: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

main.o: main.c

scanner.o: scanner.c scanner.h

simpson.o: simpson.c simpson.h

parser.o: parser.c parser.h

stqu.o: stqu.c stqu.h

ast.o: ast.c ast.h

clean:
	rm -f $(OBJS) $(TARGET)
