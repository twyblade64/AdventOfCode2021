#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream data("input_07_1.txt");
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
	for (int i = 0; i < numbers.size(); ++i){
		std::cout << numbers[i];
		if (i+1 < numbers.size())
			std::cout << ",";
	}
	std::cout << std::endl;

	int count = 0;
	int left = 0;
	int right = numbers.size() - 1;
	int leftW = 1;
	int rightW = 1;
	while(left != right) {
		std::cout << numbers[left] << "(" << leftW << ")" << " - " << numbers[right] << "(" << rightW << ")" << " " << count << std::endl;
		if (leftW <= rightW)
		{
			if (numbers[left + 1] != numbers[left]) count += leftW * (numbers[left+1] - numbers[left]);
			++leftW;
			++left;
		} else {
			if (numbers[right - 1] != numbers[right]) count += rightW * (numbers[right] - numbers[right - 1]);
			++rightW;
			--right;
		}
	}

	std::cout << count << std::endl;
	return 0;
}
