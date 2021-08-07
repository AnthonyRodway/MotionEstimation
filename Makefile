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

all: $(MAIN)

$(MAIN): $(MAIN).c
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN).c $(BMP).c $(SAD).c 

second: $(MAIN)

$(MAIN_U): $(MAIN).c
	$(CC) $(CFLAGS) -o $(MAIN_U) $(MAIN).c $(BMP).c $(SAD_1).c 

third: $(MAIN)

$(MAIN_U): $(MAIN).c
	$(CC) $(CFLAGS) -o $(MAIN_U) $(MAIN).c $(BMP).c $(SAD_2).c 

clean:
	@echo "Cleaning All Executables" 
	$(RM) $(MAIN) 
	$(RM) $(MAIN_U)