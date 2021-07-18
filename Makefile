# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# the build MAIN executable:
MAIN = main

all: $(MAIN)

$(MAIN): $(MAIN).c
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN).c

clean:
	$(RM) $(MAIN) 