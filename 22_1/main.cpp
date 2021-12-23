#include <iostream>
#include <fstream>
#include <sstream>

int ExtractInteger(const std::string s, int &position) {
	bool numberStarted = false;
	bool positive = true;
	int n = 0;
	while (position < s.size()) {
		if (s[position] - '0' >= 0 && s[position] - '0' < 10) {
			n = n * 10 + s[position] - '0';
			numberStarted = true;
		} else {
			if (numberStarted)
				break;
			if (s[position] == '-') {
				positive = false;
				numberStarted = true;
			}
		}
		++position;
	}

	return n * (positive ? 1 : -1);
}

int main() {
	std::ifstream data("input_22_1.txt");
	if (!data.is_open()) return -1;

	bool cubeState[101 * 101 * 101]{};

	std::string line;
	while (data >> line) {
		bool on = line.compare("on") == 0;
		int minX, minY, minZ, maxX, maxY, maxZ;

		int parsePosition = 0;
		data >> line;
		minX = ExtractInteger(line, parsePosition);
		maxX = ExtractInteger(line, parsePosition);
		minY = ExtractInteger(line, parsePosition);
		maxY = ExtractInteger(line, parsePosition);
		minZ = ExtractInteger(line, parsePosition);
		maxZ = ExtractInteger(line, parsePosition);

		for (int x = minX; x <= maxX; ++x)
			for (int y = minY; y <= maxY; ++y)
				for (int z = minZ; z <= maxZ; ++z)
					cubeState[(x + 50) + (y + 50) * 101 + (z + 50) * 101 * 101] = on;
	}

	int count = 0;
	for (int i = 0, n = 101 * 101 * 101; i < n; ++i)
		if (cubeState[i])
			++count;

	std::cout << count << std::endl;
	return 0;
}
