# 1. first state the compiler
# 2. set flags 
# (www.gnu.org/software/make/manual/make.pdf)
# 3. call (it targets the first)
# 4. setup rules

# set the compiler
CC = gcc
# all warnings and optimization level 2
CFLAGS = -Wall -O2
# wildcard is a function that returns a list of all files that match the pattern
SRCS = $(wildcard *.c) 

# substitute the .c with nothing
EXES = $(SRCS:.c=)

# Default target
all: $(EXES)

# Rule to compile each .c to an executable with the same base name
# $@ corresponds to the target name
# $< is the first prerequisite
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXES)