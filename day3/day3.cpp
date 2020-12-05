#include <array>
#include <iostream>

class taboggan_trajectory
{
public:
	taboggan_trajectory(int move_right, int move_down) :
		move_right(move_right),
		move_down(move_down),
		h_position(0),
		row_counter(0),
		tree_counter(0) { }

	void next(const char* row, int length) {
		if (row_counter % move_down == 0) {
			if (row[h_position] == '#') {
				tree_counter++;
			}
			h_position = (h_position + move_right) % length;
		}
		row_counter++;
	}
	int tree_count() const { return tree_counter; }
private:
	int move_right;
	int move_down;
	int h_position;
	int row_counter;
	int tree_counter;
};

int main() {
	std::array<taboggan_trajectory, 5> trajectories = {
		taboggan_trajectory(1, 1),
		taboggan_trajectory(3, 1),
		taboggan_trajectory(5, 1),
		taboggan_trajectory(7, 1),
		taboggan_trajectory(1, 2)
	};
	std::string input;
	while (std::cin >> input) {
		for (auto it = trajectories.begin();
		     it != trajectories.end(); ++it) {
			it->next(input.c_str(), input.length());
		}
	}
	std::cout << "1st answer: " << trajectories[1].tree_count() << std::endl;
	long result = 1;
	for (auto it = trajectories.begin();
			it != trajectories.end(); ++it) {
		result *= it->tree_count();
	}
	std::cout << "2nd answer: " << result << std::endl;
	return 0;
}
