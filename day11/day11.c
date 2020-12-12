#include <stdio.h>
#include <stdlib.h>

#define BUSY '#'
#define FREE 'L'
#define FLOOR '.'

#define SWAP(A, B, TEMP) (TEMP)=(A);(A)=(B);(B)=(TEMP);

int is_busy(char **source, int rows, int columns, int i, int j) {
	int result = 0;
	if (i >= 0 && i < rows && j >= 0 && j < columns) {
		result = source[i][j] == BUSY;
	}
	return result;
}

int apply_rules_adjacent(char **source, char **dest, int rows, int columns) {
	int i, j, changes = 0, count_adj_busy;
	char seat;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < columns; ++j) {
			seat = source[i][j];
			if (seat != FLOOR) {
				count_adj_busy =
					is_busy(source, rows, columns, i - 1, j - 1) +
					is_busy(source, rows, columns, i - 1, j) +
					is_busy(source, rows, columns, i - 1, j + 1) +
					is_busy(source, rows, columns, i, j - 1) +
					is_busy(source, rows, columns, i, j + 1) +
					is_busy(source, rows, columns, i + 1, j - 1) +
					is_busy(source, rows, columns, i + 1, j) +
					is_busy(source, rows, columns, i + 1, j + 1);
				if (seat == BUSY) {
					if (count_adj_busy >= 4) {
						dest[i][j] = FREE;
						changes++;
						continue;
					}
				} else if (count_adj_busy == 0) {
					dest[i][j] = BUSY;
					changes++;
					continue;
				}
			}
			dest[i][j] = seat;
		}
	}
	return changes;
}

int can_see_busy(char **source, int rows, int columns, int i, int j, int move_i, int move_j) {
	int result = 0;
	i += move_i;
	j += move_j;
	while (i >= 0 && i < rows && j >= 0 && j < columns) {
		if (source[i][j] != FLOOR) {
			if (source[i][j] == BUSY) { result++; }
			break;
		}
		i += move_i;
		j += move_j;
	}
	return result;
}

int apply_rules_visibility(char **source, char **dest, int rows, int columns) {
	int i, j, changes = 0, count_visible_busy;
	char seat;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < columns; ++j) {
			seat = source[i][j];
			if (seat != FLOOR) {
				count_visible_busy =
					can_see_busy(source, rows, columns, i, j, -1, -1) +
					can_see_busy(source, rows, columns, i, j, -1, 0) +
					can_see_busy(source, rows, columns, i, j, -1, 1) +
					can_see_busy(source, rows, columns, i, j, 0, -1) +
					can_see_busy(source, rows, columns, i, j, 0, 1) +
					can_see_busy(source, rows, columns, i, j, 1, -1) +
					can_see_busy(source, rows, columns, i, j, 1, 0) +
					can_see_busy(source, rows, columns, i, j, 1, 1);
				if (seat == BUSY) {
					if (count_visible_busy >= 5) {
						dest[i][j] = FREE;
						changes++;
						continue;
					}
				} else if (count_visible_busy == 0) {
					dest[i][j] = BUSY;
					changes++;
					continue;
				}
			}
			dest[i][j] = seat;
		}
	}
	return changes;
}

int count_busy(char **grid, int rows, int columns) {
	int i, j, busy = 0;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < columns; ++j) {
			if (grid[i][j] == BUSY) {
				busy++;
			}
		}
	}
	return busy;
}

int main() {
	int rows, columns, i, changed;
	char **original, **current, **next, **temp;
	scanf("%d %d\n", &rows, &columns);
	original = (char**)malloc(rows * sizeof(char*));
	current = (char**)malloc(rows * sizeof(char*));
	next = (char**)malloc(rows * sizeof(char*));
	for (i = 0; i < rows; ++i) {
		original[i] = (char*)malloc((columns + 3) * sizeof(char));
		current[i] = (char*)malloc((columns + 3) * sizeof(char));
		next[i] = (char*)malloc((columns + 3) * sizeof(char));
		fgets(original[i], columns + 3, stdin);
	}

	changed = apply_rules_adjacent(original, current, rows, columns);
	while (changed) {
		changed = apply_rules_adjacent(current, next, rows, columns);
		SWAP(current, next, temp);
	}
	printf("1st solution: %4d\n", count_busy(current, rows, columns));

	changed = apply_rules_visibility(original, current, rows, columns);
	while (changed) {
		changed = apply_rules_visibility(current, next, rows, columns);
		SWAP(current, next, temp);
	}
	printf("2nd solution: %4d\n", count_busy(current, rows, columns));
	return 0;
}
