all: ninth

ninth: ninth.c
	gcc -lm -Wall -Werror -fsanitize=address -std=c11 ninth.c -o ninth

clean:
	rm -rf ninth
