#include <algorithm>
#include <iostream>
#include <vector>

bool try_find_sum(
	int expectedSum,
	std::vector<int>::const_iterator& left,
	std::vector<int>::const_iterator& right) {
	while (*left <= *right) {
		int sum = *left + *right;
		if (sum == expectedSum) {
			return true;
		} else if (sum < expectedSum) {
			left++;
		} else {
			right--;
		}
	}
	return false;
}

int main() {
	const int expectedSum = 2020;
	int n;
	std::vector<int> numbers;
	while (std::cin >> n) {
		if (n < expectedSum) {
			numbers.push_back(n);
		}
	}
	std::sort(numbers.begin(), numbers.end());
	// Find the two integers that sum to `expectedSum`
	// by using the two-pointers method.
	auto first = numbers.cbegin();
	auto second = --numbers.cend();
	bool found = try_find_sum(expectedSum, first, second);
	if (found) {
		std::cout << "First solution: " << (*first * *second) << std::endl;
	}
	found = false;
	// Find the three integers that sum to `expectedSum`
	// by fixing one integer (`third`) and by applying the
	// previous method to the remaining values.
	auto it = numbers.cbegin();
	int third;
	for (; !found && it != numbers.cend() - 2; ++it) {
		first = it + 1;
		second = --numbers.cend();
		third = *it;
		found = try_find_sum(expectedSum - third, first, second);
	}
	if (found) {
		std::cout << "Second solution: " << (*first * *second * third) << std::endl;
	}
	return 0;
}
