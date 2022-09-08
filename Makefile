main: main.c fraction.c row.c
	gcc main.c fraction.c row.c -o main -Wall -Wextra -pedantic -std=c99
