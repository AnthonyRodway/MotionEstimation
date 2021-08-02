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
TEST = test

MAIN_U = main_unoptimized
SAD_U = sad_unoptimized

unoptimized: $(MAIN_U)

$(MAIN_U): $(MAIN_U).c
	$(CC) $(CFLAGS) -o $(MAIN_U) $(MAIN_U).c $(BMP).c $(SAD_U).c $(TEST).c


all: $(MAIN)

$(MAIN): $(MAIN).c
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN).c $(BMP).c $(SAD).c $(TEST).c


clean:
	@echo "Cleaning All Executables" 
	$(RM) $(MAIN) 
	$(RM) $(MAIN_U)