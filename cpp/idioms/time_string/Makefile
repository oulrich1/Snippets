
CC		=		g++
CFLAGS	=		-Wall -pedantic -g
OBJS	=		time_string.o
TARGET	=		time

SRC=
INC=

CPPLIB= -lrt -lm

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) main.cpp -o main $(OBJS) $(CPPLIB)

time_string.o: time_string.cpp
	$(CC) $(CFLAGS) $< -c -o $@ $(CPPLIB)

clean:
	rm -f $(TARGET) $(OBJS)
