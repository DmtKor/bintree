build:
	gcc -Wall -O2 -Wextra -o ./prog ./src/bintree.c ./src/main.c ./src/panic.c ./src/readarr.c

debug:
	gcc -g -Wall -Wextra -o ./prog ./src/bintree.c ./src/main.c ./src/panic.c ./src/readarr.c

run:
	./prog > output.txt < input.txt
