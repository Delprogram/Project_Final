CC = gcc
TARGET = pathfinding
SRCS = $(wildcard *.c)

all :
	$(CC) $(SRCS) -o $(TARGET) -lm

clean :
	rm -f $(TARGET)

re : clean all