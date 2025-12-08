.PHONY: all compile run clean

all: clean compile run

compile:
	@g++ --std=c++11 main.cpp -o main

run: compile
	@./main

clean:
	@rm -f main