#include <stdio.h>
#include <limits.h>

#define MAX_N_BUS 10

typedef struct s_egcd {
	long gcd;
	long x;
	long y;
} egcd;

/*
 * In addition to the greatest common divisor (gcd) of integers a and b,
 * it computes also the coefficients of Bézout's identity,
 * which are integers x and y such that:
 * a*x + b*y = gcd
 */
egcd extended_euclidean_algorithm(long a, long b) {
	if (a == 0) {
		egcd result = { b, 0, 1 };
		return result;
	} else {
		egcd intermediate = extended_euclidean_algorithm(b % a, a);
		egcd result = { intermediate.gcd, intermediate.y - (b / a) * intermediate.x, intermediate.x };
		return result;
	}
}

int main() {
	int current_time, bus_interval, i = 0, wait_time, modulo;
	int bus_indexes[MAX_N_BUS];
	int bus_intervals[MAX_N_BUS];
	int bus_count = 0;
	char lineBuffer[10];
	int min_wait_bus_interval = -1;
	int min_wait_time = INT_MAX;
	long temp;
	long lcm_of_bus_intervals = 1;
	long unknown_departure_time = 0;
	scanf("%d\n", &current_time);
	while (fgets(lineBuffer, 10, stdin)) {
		if (lineBuffer[0] == 'x') {
			i++;
		} else if (sscanf(lineBuffer, "%d", &bus_interval)) {
			/* Code for first solution */
			modulo = current_time % bus_interval;
			if (modulo == 0) {
				wait_time = 0;
			} else {
				wait_time = bus_interval - modulo;
			}
			if (wait_time < min_wait_time) {
				min_wait_time = wait_time;
				min_wait_bus_interval = bus_interval;
			}
			/* Store values for second solution */
			bus_intervals[bus_count] = bus_interval;
			bus_indexes[bus_count] = i;
			bus_count++;
			lcm_of_bus_intervals *= bus_interval;
			i++;
		}
	}
	printf("1st solution: %20d\n", min_wait_bus_interval * min_wait_time);
	/*
	 * About the second solution.
	 *
	 * Each bus should be the i-th departing bus, so
	 * (unknown_departure_time + i) % bus_interval = 0
	 * or:
	 * unknown_departure_time + i ≡ 0 (mod bus_interval)
	 * unknown_departure_time ≡ bus_interval - i (mod bus_interval)
	 * The output is a set of equations in the form:
	 *    x ≡ a_i (mod n_i)
	 * which, under the condition that all n_0...n_k values are pairwise
	 * coprime, has a unique solution and can be solved with
	 * the Chinese Remainder Theorem.
	 *
	 * https://en.wikipedia.org/wiki/Chinese_remainder_theorem
	 *
	 * x = sum{i=0...k}( a_i * N_i * M_i )
	 * N = prod{i=0...k}( n_i ) ---> lcm_of_bus_intervals
	 * N_i = N / n_i
	 * M_i is one of Bézout integers that solve the formula:
	 * M_i*N_i + m_i*n_i = 1 ----> (x*a + x*b = 1)
	 */
	for (i = 0; i < bus_count; ++i) {
		temp = lcm_of_bus_intervals / bus_intervals[i];
		unknown_departure_time += (bus_intervals[i] - bus_indexes[i])
			* temp
			* ((extended_euclidean_algorithm(temp, bus_intervals[i]).x % bus_intervals[i] + bus_intervals[i]) % bus_intervals[i]);
	}
	unknown_departure_time %= lcm_of_bus_intervals;
	printf("2nd solution: %20ld\n", unknown_departure_time);
	return 0;
}
