CC = gcc

release/fintrack: main.o llfunc.o
	gcc main.o llfunc.o -o release/fintrack
	clean

main.o: main.s
	as main.s -o main.o

main.s: main.i
	gcc -S main.i -o main.s

main.i: src/main.c logs/transaction_log.txt
	gcc -E src/main.c -o main.i

llfunc.o: llfunc.s
	as llfunc.s -o llfunc.o

llfunc.s: llfunc.i
	gcc -S src/llfunc.i -o llfunc.s

llfunc.i: src/llfunc.c logs/transaction_log.txt
	gcc -E src/llfunc.c -o llfunc.i

logs/transaction_log.txt:
	touch logs/transaction_log.txt

clean:
	rm -rf *.o
	rm -rf *.s
	rm -rf *.i
