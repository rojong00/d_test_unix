CC		:=gcc
CFLAGS	:=-Wall -g -O2

TARGET	:=exec
SRC		:=$(wildcard *.c)
OBJ		:=$(SRC: .c=.o)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $<

main.o	: main.c music.h

clean:
	rm -f *.o
	rm -f $(TARGET)
