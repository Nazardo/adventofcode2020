#include <ctype.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 30
#define LEN(a) (sizeof(a)/sizeof(*(a)))

void analyze_and_reset(
	int *answers_by_question,
	int length,
	int group_size,
	int* any_answer,
	int* everyone_answer) {
	while (length--) {
		if (answers_by_question[length] > 0) {
			if (answers_by_question[length] == group_size) {
				*everyone_answer = *everyone_answer + 1;
			}
			*any_answer = *any_answer + 1;
			answers_by_question[length] = 0;
		}
	}
}

int main() {
	char line[MAX_LINE_LENGTH];
	int counters['z' - 'a' + 1] = { 0 };
	int i, group_size = 0,
	    sum_anyone_answer = 0, sum_everyone_answer = 0;
	while (fgets(line, sizeof line, stdin) != NULL) {
		for(i = 0; islower(line[i]); ++i) {
			counters[line[i]-'a']++;
		}
		if (i == 0) {
			analyze_and_reset(
				counters, LEN(counters),
				group_size,
				&sum_anyone_answer,
				&sum_everyone_answer);
			group_size = 0;
		} else {
			group_size++;
		}
	}
	analyze_and_reset(
		counters, LEN(counters),
		group_size,
		&sum_anyone_answer,
		&sum_everyone_answer);
	printf("1st solution: %3d\n", sum_anyone_answer);
	printf("2nd solution: %3d\n", sum_everyone_answer);
	return 0;
}
