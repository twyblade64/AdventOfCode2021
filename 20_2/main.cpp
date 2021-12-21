#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

#define Position std::pair<int,int>

struct PositionHash {
	std::size_t operator()(const Position &position) const {
		return (std::hash<int>()(position.first) & 0XFF) | (std::hash<int>()(position.second) << 16);
	}
};

int main() {
	std::ifstream data("input_20_2.txt");
	if (!data.is_open()) return -1;

	std::unordered_set<Position, PositionHash> baseImage;
	std::unordered_set<Position, PositionHash> tempImage;
	int minX, minY, maxX, maxY;
	minX = minY = maxX = maxY = 0;
	bool table[512];
	std::string line;
	std::getline(data, line);
	for (int i = 0; i < 512; ++i)
		table[i] = line[i] == '#';

	std::getline(data, line);
	while (std::getline(data, line)) {
		maxX = line.size();
		++maxY;
		for (int i = 0; i < maxX; ++i)
			if (line[i] == '#')
				baseImage.emplace(Position(i, maxY - 1));
	}

	--minX;
	--minY;
	++maxX;
	++maxY;

	bool infiniteOn = false;
	for (int z = 0; z < 50; ++z) {
		std::cout << "Zoom: " << z << " " << baseImage.size() << std::endl;
		for (int y = minY; y < maxY; ++y) {
			for (int x = minX; x < maxX; ++x) {
				int v = 0;
				for (int oY = -1; oY <= 1; ++oY) {
					for (int oX = -1; oX <= 1; ++oX) {
						Position pos = Position(x + oX, y + oY);
						if (pos.first >= minX && pos.second >= minY && pos.first < maxX && pos.second < maxY)
						v = (v << 1) + (baseImage.find(pos) != baseImage.end() ? 1 : 0);
						else
							v = (v << 1) + (infiniteOn ? 1 : 0);
					}
				}
				if (table[v])
					tempImage.emplace(x, y);
			}
		}

		--minX;
		--minY;
		++maxX;
		++maxY;
		infiniteOn = table[infiniteOn ? 0x1FF : 0x0];
		if (infiniteOn) {
			for (int y = minY; y < maxY; ++y)
				for (int x = minX; x < maxX; ++x)
					if (y == minY || y == maxY - 1 || x == minX || x == maxX - 1)
						tempImage.emplace(Position(x, y));
		}

		baseImage.swap(tempImage);
		tempImage.clear();
	}

	std::cout << baseImage.size() << " " << infiniteOn << std::endl;

	return 0;
}
