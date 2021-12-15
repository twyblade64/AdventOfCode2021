#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <map>
#include <vector>
#include <limits>

#define charPair std::pair<char, char>

int main() {
	std::ifstream data("input_14_2.txt");
	if (!data.is_open()) return -1;

	std::map<charPair, std::pair<charPair, charPair>> generationTable;
	std::map<charPair, long long int> pairCountA;
	std::map<charPair, long long int> pairCountB;

	std::string line;
	std::getline(data, line);
	char firstChar = line[0];
	char lastChar = line[line.size() - 1];
	for (int i = 0; i < line.size() - 1; ++i) {
		charPair pair(line[i], line[i + 1]);
		if (pairCountA.find(pair) == pairCountA.end()) pairCountA.emplace(pair, 0);
		++pairCountA[pair];
	}

	data.ignore();
	while (std::getline(data, line)) {
		charPair from(line[0], line[1]);
		charPair a(line[0], line[6]);
		charPair b(line[6], line[1]);
		generationTable.emplace(from, std::pair<charPair, charPair >(a, b));
	}

	int iterations = 40;
	for (int i = 0; i < iterations; ++i) {
		for (auto &pairCount: pairCountA) {
			if (generationTable.find(pairCount.first) == generationTable.end()) {
				if (pairCountB.find(pairCount.first) == pairCountB.end()) pairCountB.emplace(pairCount.first, 0);
				pairCountB[pairCount.first] += pairCount.second;
			} else {
				auto pairPair = generationTable[pairCount.first];
				if (pairCountB.find(pairPair.first) == pairCountB.end()) pairCountB.emplace(pairPair.first, 0);
				if (pairCountB.find(pairPair.second) == pairCountB.end()) pairCountB.emplace(pairPair.second, 0);
				pairCountB[pairPair.first] += pairCount.second;
				pairCountB[pairPair.second] += pairCount.second;
			}
		}

		pairCountA.swap(pairCountB);
		pairCountB.clear();
	}

	std::map<char, long long int> charCount;
	charCount.emplace(firstChar, 1);
	charCount.emplace(lastChar, 1);
	for (auto &pairCount: pairCountA) {
		if (charCount.find(pairCount.first.first) == charCount.end()) charCount.emplace(pairCount.first.first, 0);
		if (charCount.find(pairCount.first.second) == charCount.end()) charCount.emplace(pairCount.first.second, 0);
		charCount[pairCount.first.first] += pairCount.second;
		charCount[pairCount.first.second] += pairCount.second;
	}

	long long int min = std::numeric_limits<long long int>::max();
	long long int max = std::numeric_limits<long long int>::min();
	long long int length = 0;
	for (auto &count: charCount) {
		length += count.second / 2;
		min = count.second / 2 < min ? count.second / 2 : min;
		max = count.second / 2 > max ? count.second / 2 : max;
	}

	std::cout << "(" << length << ")\t" << max << " - " << min << " = " << max - min << std::endl;

	return 0;
}
