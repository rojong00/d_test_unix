CC		:=gcc
CFLAGS	:=-Wall -Werror -Wextra -g -O2 
#CFLAGS	:=-Wall -g -O2 

TARGET	:=exec
SRCS	:=select_2.c
OBJS	:=$(SRCS:.c=.o)

$(TARGET)	:$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS)		:$(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o
	rm $(TARGET)
