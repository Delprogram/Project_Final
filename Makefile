CC = gcc
CFLAGS = -Wall -g -lm
TARGET = pathfinding
SRCS = $(wildcard *.c)

all :
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) -lm

clean :
	rm -f $(TARGET)

re : clean all