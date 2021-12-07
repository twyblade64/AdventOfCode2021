#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream data("input_07_2.txt");
	if (!data.is_open()) return -1;

	std::string input;
	data >> input;
	std::stringstream ss(input);

	int n;
	std::vector<int> numbers;
	while (ss >> n) {
		numbers.push_back(n);
		ss.ignore();
	}

	std::sort(numbers.begin(), numbers.end());
	for (int i = 0; i < numbers.size(); ++i) {
		std::cout << numbers[i];
		if (i + 1 < numbers.size())
			std::cout << ",";
	}
	std::cout << std::endl;

	int count = 0;
	int left = 0;
	int right = numbers.size() - 1;
	int leftWeight = 1;
	int leftShips = 1;
	int rightWeight = 1;
	int rightShips = 1;
	while (left != right) {
		std::cout << left << "(" << leftWeight << ")[" << leftShips << "] - "
				  << right << "(" << rightWeight << ")[" << rightShips << "] " << count << std::endl;

		if (leftWeight <= rightWeight) {
			if (numbers[left] != numbers[left + 1]) {
				++numbers[left];
				count += leftWeight;
				leftWeight += leftShips;
			} else {
				++leftWeight;
				++leftShips;
				++left;
			}
		} else {
			if (numbers[right] != numbers[right - 1]) {
				--numbers[right];
				count += rightWeight;
				rightWeight += rightShips;
			} else {
				++rightWeight;
				++rightShips;
				--right;
			}
		}
	}

	std::cout << count << std::endl;
	return 0;
}
