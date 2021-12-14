#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <cstdlib>

struct Vector2 {
public:
	int x;
	int y;

	Vector2(int x, int y) : x(x), y(y) {}
};

inline bool operator==(Vector2 const &lhs, Vector2 const &rhs) { return (lhs.x == rhs.x) && (lhs.y == rhs.y); }

struct Vector2Hash {
	size_t operator()(const Vector2 &interval) const { return std::hash<int>()(interval.x | (interval.y << 16)); }
};

int main() {
	std::ifstream data("input_13_2.txt");
	if (!data.is_open()) return -1;

	int width = 0;
	int height = 0;

	std::unordered_set<Vector2, Vector2Hash> setA;
	std::unordered_set<Vector2, Vector2Hash> setB;

	std::string line;
	while (std::getline(data, line)) {
		if (line.empty())
			break;
		std::stringstream ss(line);
		int x, y;
		ss >> x;
		ss.ignore();
		ss >> y;
		setA.emplace(Vector2(x, y));
		if (x + 1 > width) width = x + 1;
		if (y + 1 > height) height = y + 1;
	}

	while (std::getline(data, line)) {
		char axis = line[11];
		int foldPos = std::atoi(line.substr(13).c_str());

		if (axis == 'x') {
			for (const auto &v: setA) {
				if (v.x < foldPos)bool pass = setB.emplace(v).second;
				else bool pass = setB.emplace(Vector2(2 * foldPos - v.x, v.y)).second;
			}
			width = foldPos;
		} else {
			for (const auto &v: setA) {
				if (v.y < foldPos)bool pass = setB.emplace(v).second;
				else bool pass = setB.emplace(Vector2(v.x, 2 * foldPos - v.y)).second;
			}
			height = foldPos;
		}

		setA.swap(setB);
		setB.clear();
	}

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
			std::cout << (setA.count(Vector2(x,y)) != 0 ? '#' : '.');
		std::cout << std::endl;
	}

	return 0;
}
