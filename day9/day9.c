#include <stdio.h>

#define FILE_SIZE 1000
#define PREAMBLE_SIZE 25

int main() {
	int number, sum_found, i, j, accumulator, min, max;
	int buffer[FILE_SIZE];
	int preamble_start = 0;
	int size = 0;
	while (size < FILE_SIZE && scanf("%d", &number)) {
		if (size >= PREAMBLE_SIZE) {
			sum_found = 0;
			for (i = 0; i < (PREAMBLE_SIZE - 1) && !sum_found; ++i) {
				for (j = 1; j < PREAMBLE_SIZE && !sum_found; ++j) {
					if (buffer[preamble_start + i] +
					    buffer[preamble_start + j] == number) {
						sum_found = 1;
					}
				}
			}
			if (!sum_found) {
				printf("1st solution: %4d\n", number);
				break;
			}
			preamble_start++;
		}
		buffer[size++] = number;
	}
	accumulator = 0;
	for (i = 0; i < size; ++i) {
		accumulator = min = max = buffer[i];
		for (j = i+1; j < size && accumulator < number; ++j) {
			accumulator += buffer[j];
			if (buffer[j] > max) { max = buffer[j]; }
			else if (buffer[j] < min) { min = buffer[j]; }
		}
		if (accumulator == number) {
			printf("2nd solution: %4d\n", min + max);
			break;
		}
	}
}
