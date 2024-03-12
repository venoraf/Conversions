all: tenth

tenth: tenth.c
	gcc -lm -Wall -Werror -fsanitize=address -std=c11 tenth.c -o tenth

clean:
	rm -rf tenth
