#include <stdio.h>
#include <stdlib.h>

int main() {
	int i, seatId, sumFromMinToMax;
	char buffer[13]; // string (9 chars) + newline (1-2 chars) + terminator
	int max = 0, min = 0x3FF, sum = 0;
	char* result = fgets(buffer, 13, stdin);
	while (result != NULL) {
		seatId = 0;
		for (i = 0; i < 10; ++i) {
			if (buffer[i] == 'B' || buffer[i] == 'R') {
				seatId |= 1 << (9 - i);
			}
		}
		if (seatId > max) {
			max = seatId;
		}
		if (seatId < min) {
			min = seatId;
		}
		sum += seatId;
		result = fgets(buffer, 13, stdin);
	}
	printf("Maximum SeatId: %4d (minimum: %4d)\n", max, min);
	sumFromMinToMax = (max - min + 1) * (min + max) / 2;
	printf("Empty seat is: %4d\n", sumFromMinToMax - sum);
	return 0;
}
