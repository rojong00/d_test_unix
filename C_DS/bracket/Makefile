CC			:=gcc
CFLAGS		:=-Wall -Werror -Wextra -g

TARGET		:=exec
SRCS		:=$(wildcard *.c)
OBJS		:=$(SRCS:.c=.o)

$(TARGET)	:$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS)		:$(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o
	rm -rf $(TARGET)
