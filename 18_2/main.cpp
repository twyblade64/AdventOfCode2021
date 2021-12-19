#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define intPair std::pair<int,int>

void Print(std::vector<intPair>& number)
{
	for (int i = 0; i < number.size(); ++i)
		std::cout << number[i].second;
	std::cout << std::endl;
	for (int i = 0; i < number.size(); ++i)
		std::cout << number[i].first;
	std::cout << std::endl << std::endl;
}

int SumMagnitude(std::vector<intPair>& a, std::vector<intPair>& b)
{
	std::vector<intPair> number;
	number.insert(number.end(), a.begin(), a.end());
	number.insert(number.end(), b.begin(), b.end());
	for (int i = 0; i < number.size(); ++i)
		++number[i].second;

	bool finished = false;
	while (!finished) {
		// Explode
		for (int i = 0; i < number.size() - 1; ++i) {
			if (number[i].second == 5) {
				if (i > 0) number[i - 1].first += number[i].first;
				if (i < number.size() - 2) number[i + 2].first += number[i + 1].first;
				number[i].first = 0;
				--number[i].second;
				number.erase(number.begin() + i + 1);
			}
		}

		// Split
		finished = true;
		for (int i = 0; i < number.size() && finished; ++i) {
			if (number[i].first >= 10) {
				intPair pair = number[i];
				number.insert(number.begin() + i + 1, intPair());
				number[i] = intPair(pair.first / 2, pair.second + 1);
				number[i + 1] = intPair(pair.first / 2 + pair.first % 2, pair.second + 1);
				finished = false;
			}
		}
	}

	for (int d = 4; d > 0; --d) {
		for (int i = 0; i + 1 < number.size(); ++i)
		{
			if (number[i].second == d) {
				number[i].first = number[i].first*3 + number[i+1].first*2;
				--number[i].second;
				number.erase(number.begin() + i + 1);
			}
		}
	}
	return number[0].first;
}

int main() {
	std::ifstream data("input_18_2.txt");
	if (!data.is_open()) return -1;

	bool first = true;
	std::vector<std::vector<intPair>> numbers;
	std::string line;
	while (std::getline(data, line)) {
		int depth = 0;
		std::vector<intPair> number;
		for (int i = 0; i < line.size(); ++i) {
			if (line[i] == '[') ++depth;
			if (line[i] == ']') --depth;
			if (line[i] >= '0' && line[i] <= '9') number.push_back(intPair(line[i] - '0', depth));
		}
		numbers.push_back(number);
	}

	int maxMagnitude = 0;
	for (int i = 0; i < numbers.size(); ++i) {
		for (int j = 0; j < numbers.size(); ++j) {
			int magnitude = SumMagnitude(numbers[i], numbers[j]);
			maxMagnitude = magnitude > maxMagnitude ? magnitude : maxMagnitude;
		}
	}

	std::cout << "Magnitude: " << maxMagnitude << std::endl;

	return 0;
}
