CC		:=gcc
CFLAGS	:=-Werror -Wall -Wextra -g

TRGT	:=exec
SRCS	:=$(wildcard *.c)
OBJS	:=$(SRCS:.c=.o)

$(TRGT)	:$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o
	rm $(TRGT)
