#include <iostream>
#include <cstdlib>

void move_point(std::pair<int, int> &point, int bearing, int amount) {
	// Only horizontal and vertical bearing are handled.
	if (bearing == 0) {
		point.second += amount;
	} else if (bearing == 180) {
		point.second -= amount;
	} else if (bearing == 90) {
		point.first += amount;
	} else if (bearing == 270) {
		point.first -= amount;
	}
}

void move_point(std::pair<int, int> &point, std::pair<int, int> movement, int amount) {
	point.first += movement.first * amount;
	point.second += movement.second * amount;
}

void rotate_around_origin(std::pair<int, int> &point, int angle) {
	// Only multiples of 90° are handled.
	int temp = point.second;
	if (angle == 90) {
		point.second = point.first * -1;
		point.first = temp;
	} else if (angle == 180) {
		point.second = point.second * -1;
		point.first = point.first * -1;
	} else if (angle == 270) {
		point.second = point.first;
		point.first = temp * -1;
	}
}

int main() {
	char movement;
	int amount;
	int bearing = 90, movement_bearing = 0;
	std::pair<int, int> position_first_solution(0, 0);
	std::pair<int, int> position_second_solution(0, 0);
	std::pair<int, int> waypoint(10, 1);
	while (std::cin >> movement >> amount) {
		movement_bearing = bearing;
		if (movement == 'R') {
			bearing = (bearing + amount) % 360;
			rotate_around_origin(waypoint, amount);
		} else if (movement == 'L') {
			bearing = (360 + bearing - amount) % 360;
			rotate_around_origin(waypoint, 360 - amount);
		} else {
			if (movement == 'N') {
				movement_bearing = 0;
			} else if (movement == 'S') {
				movement_bearing = 180;
			} else if (movement == 'E') {
				movement_bearing = 90;
			} else if (movement == 'W') {
				movement_bearing = 270;
			}
			move_point(position_first_solution, movement_bearing, amount);
			if (movement == 'F') {
				move_point(position_second_solution, waypoint, amount);
			} else {
				move_point(waypoint, movement_bearing, amount);
			}
		}
	}
	std::cout << "1st Final position (x: " << position_first_solution.first << ", y: " << position_first_solution.second << ")" << std::endl;
	std::cout << "1st solution: " << abs(position_first_solution.first) + abs(position_first_solution.second) << std::endl;
	std::cout << "2nd Final position (x: " << position_second_solution.first << ", y: " << position_second_solution.second << ")" << std::endl;
	std::cout << "2nd solution: " << abs(position_second_solution.first) + abs(position_second_solution.second) << std::endl;
}
