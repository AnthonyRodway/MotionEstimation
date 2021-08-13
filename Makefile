# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# the build MAIN executable:
MAIN = main
BMP = bmp_parser
SAD = ./sad/sad
SAD1 = ./sad1/sad
SAD2 = ./sad2/sad
SAD3 = ./sad3/sad

all: basic first second third

basic: $(MAIN).c 
	$(CC) $(CFLAGS) -o sad_executable $(MAIN).c $(BMP).c $(SAD).c 
 
first: $(MAIN).c
	$(CC) $(CFLAGS) -o sad1_executable $(MAIN).c $(BMP).c $(SAD1).c 

second: $(MAIN).c
	$(CC) $(CFLAGS) -o sad2_executable $(MAIN).c $(BMP).c $(SAD2).c 

third: $(MAIN).c
	$(CC) $(CFLAGS) -o sad3_executable $(MAIN).c $(BMP).c $(SAD3).c 

clean:
	@echo "Cleaning All Executables" 
	$(RM) sad_executable
	$(RM) sad1_executable
	$(RM) sad2_executable
	$(RM) sad3_executable