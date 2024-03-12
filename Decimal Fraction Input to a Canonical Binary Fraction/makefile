all: seventh

seventh: seventh.c
	gcc -lm -Wall -Werror -fsanitize=address -std=c11 seventh.c -o seventh

clean:
	rm -rf seventh
