CC = gcc

all: release/fintrack logs/transaction_log.txt clean dist

release/fintrack: main.o llfunc.o
	gcc main.o llfunc.o -o release/fintrack

main.o: main.s
	as main.s -o main.o

llfunc.o: llfunc.s
	as llfunc.s -o llfunc.o

main.s: main.i
	gcc -S main.i -o main.s

llfunc.s: llfunc.i
	gcc -S llfunc.i -o llfunc.s

main.i: src/main.c logs/transaction_log.txt
	gcc -E src/main.c -o main.i

llfunc.i: src/llfunc.c logs/transaction_log.txt
	gcc -E src/llfunc.c -o llfunc.i

logs/transaction_log.txt:
	touch logs/transaction_log.txt

.PHONY: clean dist

dist:
	zip -r fintrack.zip src/ include/ logs/transaction_log.txt report/ Makefile
	mv fintrack.zip dist

clean:
	rm -rf *.o
	rm -rf *.s
	rm -rf *.i
