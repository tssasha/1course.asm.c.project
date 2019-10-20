all: functions.asm prog

clean:
	rm -rf prog *.o

generation.o: generation.c
	gcc generation.c -c -o generation.o -m32

gen: generation.o 
	gcc generation.o -o gen -m32

functions.asm: $(SPEC_FILE) gen
	./gen $(SPEC_FILE)

functions.o: functions.asm
	nasm -f elf32 functions.asm -o functions.o

main.o: main.c
	gcc main.c -c -o main.o -m32

prog: main.o functions.o
	gcc functions.o main.o -o prog -m32