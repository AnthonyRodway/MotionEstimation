# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall 

# the build MAIN executable:
MAIN = main
BMP = bmp_parser
SAD = sad
SAD_1 = sad1
SAD_2 = sad2
SAD_3 = sad3

default: basic

all: basic second third fourth

basic: $(MAIN).c 
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN).c $(BMP).c $(SAD).c 
 
second: $(MAIN).c
	$(CC) $(CFLAGS) -o main1 $(MAIN).c $(BMP).c $(SAD_1).c 

third: $(MAIN).c
	$(CC) $(CFLAGS) -o main2 $(MAIN).c $(BMP).c $(SAD_2).c 

fourth: $(MAIN).c
	$(CC) $(CFLAGS) -o main3 $(MAIN).c $(BMP).c $(SAD_3).c 

clean:
	@echo "Cleaning All Executables" 
	$(RM) $(MAIN)
	$(RM) main1
	$(RM) main2
	$(RM) main3