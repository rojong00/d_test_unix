CC		:=gcc
CFLAGS	:=-Wall -Werror -Wextra -O2 -g 

TARGET	:=./d_eXec/exec
SRCS	:=$(wildcard d_src/*.c)
OBJS	:=$(SRCS:d_src/.c=d_src/.o)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS)	-o $@ $^ -I./d_hdr -lpthread

func.o	: func.c
	$(CC) $(CFLAGS) -c -o $@ $< -I./d_hdr

pth.o	: pth.c
	$(CC) $(CFLAGS) -c -o $@ $< -I./d_hdr/

main.o	: main.c
	$(CC) $(CFLAGS) -c -o $@ $< -I./d_hdr

clean	:
	rm -rf $(TARGET)
	rm -rf *.o
