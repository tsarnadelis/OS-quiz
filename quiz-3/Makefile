SHELL := /bin/bash


# ============================================
# COMMANDS

CC = gcc -O3 -Wall 
RM = rm -f

# ==========================================
# TARGETS


EXECUTABLES = parent child

all: $(EXECUTABLES)

parent: parent.c
	$(CC) $< -o $@

child: child.c
	$(CC) $< -o $@

install: all
	mkdir -p ~/quiz-3/bins
	cp parent ~/quiz-3/bins/parent
	cp child ~/quiz-3/bins/child

clean:
	$(RM) *.o *~ $(EXECUTABLES)
