#include <stdio.h>
#include <string.h>

int is_valid_policy1(int min, int max, char character, char* string) {
	int count = 0;
	for (int i = 0; string[i] != '\0' && count <= max; ++i) {
		if (string[i] == character) {
			count++;
		}
	}
	return count >= min && count <= max;
}

int is_valid_policy2(int min, int max, char character, char* string) {
	return string[min-1] == character ^ string[max-1] == character;
}

int main() {
	int left, right, count1 = 0, count2 = 0;
	char character;
	char buffer[40];
	char* result = fgets(buffer, 40, stdin);
	while (result != NULL) {
		sscanf(buffer, "%d-%d %c", &left, &right, &character);
		result = strrchr(buffer, ' ') + 1;
		if (is_valid_policy1(left, right, character, result)) {
			count1++;
		}
		if (is_valid_policy2(left, right, character, result)) {
			count2++;
		}
		result = fgets(buffer, 40, stdin);
	}
	printf("Valid passwords policy 1: %3d\n", count1);
	printf("Valid passwords policy 2: %3d\n", count2);
	return 0;
}
