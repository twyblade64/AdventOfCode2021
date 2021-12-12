#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

int main() {
	std::ifstream data("input_11_2.txt");
	if (!data.is_open()) return -1;

	int width, height = 0;
	std::vector<int> map;

	std::string input;
	while (data >> input) {
		width = input.size();
		for (int i = 0; i < width; ++i)
			map.push_back(input[i] - '0');
		++height;
	}

	int flashRange = 1;
	int s;
	int simulationSteps = 1000;
	for (s = 0; s < simulationSteps; ++s) {
		// Flash
		int count = 0;
		std::stack<int> pendingFlash;
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				if (++map[x + y * width] == 10)
					pendingFlash.push(x + y * width);
				while (!pendingFlash.empty()) {
					++count;
					int pos = pendingFlash.top();
					pendingFlash.pop();
					int posX = pos % width;
					int posY = pos / width;
					for (int fX = posX - flashRange; fX <= posX + flashRange; ++fX) {
						for (int fY = posY - flashRange; fY <= posY + flashRange; ++fY) {
							if (fX == posX && fY == posY) continue;
							if (fX < 0 || fY < 0 || fX >= width || fY >= height) continue;
							if (++map[fX + fY * width] == 10)
								pendingFlash.push(fX + fY * width);
						}
					}
				}
			}
		}

		// Reset
		for (int i = 0; i < width * height; ++i)
			if (map[i] >= 10) map[i] = 0;

		if (count == width * height)
			break;
	}

	// Print Map
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			std::cout << map[x + y * width];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << s+1 << std::endl;

	return 0;
}
