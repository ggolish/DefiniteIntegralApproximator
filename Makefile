CFLAGS = -Wall -g -Iinclude
CC = gcc

.SUFFIXES: .c .o

.c.o:
	$(CC) -c $(CFLAGS) $*.c -o $*.o

OBJS = \
	src/ast.c	\
	src/main.c	\
	src/parser.c	\
	src/scanner.c	\
	src/simpson.c	\
	src/stqu.c	\

TARGET = integrate

default: $(TARGET)

$(TARGET): $(OBJS:.c=.o)
	$(CC) $(CFLAGS) $^ -o $(TARGET) -lm

ast.o: src/ast.c include/ast.h

main.o: src/main.c include/simpson.h include/parser.h include/ast.h

parser.o: src/parser.c include/parser.h include/stqu.h

scanner.o: src/scanner.c include/scanner.h

simpson.o: src/simpson.c include/simpson.h

stqu.o: src/stqu.c include/stqu.h

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f src/ast.o
	rm -f src/main.o
	rm -f src/parser.o
	rm -f src/scanner.o
	rm -f src/simpson.o
	rm -f src/stqu.o
	rm -f $(TARGET)
