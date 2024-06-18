CC		:=gcc
CFLAGS	:=-Wall -g -O2

TARGET	:=exec
SRC		:=$(wildcard *.c)
OBJ		:=$(SRC: .c=.o)
HDR		:=$(wildcard *.h)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $<

#$(OBJ) : $(SRC) $(HDR)
#	$(CC) $(CFLAGS) -o -c $@ $<
main.o	: main.c prac2.h

clean:
	rm -f *.o
	rm -f $(TARGET)
