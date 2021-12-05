#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

#define BOARD_SIZE 5

class Map {
public:
	int *values;
	int width;
	int height;
	int dangerCount;

	Map(int width, int height) : width(width), height(height) {
		values = new int[width * height];
		memset(values, 0, sizeof(int) * (width * height));
		dangerCount = 0;
	}

	~Map() {
		delete[] values;
	}

	void Line(int x1, int y1, int x2, int y2) {
		// Bressenham
		int dx, dy, incx, incy, balance;
		incx = x2 > x1 ? 1 : -1;
		incy = y2 > y1 ? 1 : -1;
		dx = (x2 - x1) * incx;
		dy = (y2 - y1) * incy;

		int px = x1, py = y1;
		if (dx >= dy) {
			balance = dy - dx;
			dx = 1;

			while (px != x2) {
				if (px >= 0 && px < width && py >= 0 && py < height) {
					int n = ++values[px + py * width];
					if (n == 2)
						++dangerCount;
				}
				if (balance >= 0) {
					py += incy;
					balance -= dx;
				}
				balance += dy;
				px += incx;
			}
		} else {
			balance = dx - dy;
			dy = 1;

			while (py != y2) {
				if (px >= 0 && px < width && py >= 0 && py < height) {
					int n = ++values[px + py * width];
					if (n == 2)
						++dangerCount;
				}
				if (balance >= 0) {
					px += incx;
					balance -= dy;
				}
				balance += dx;
				py += incy;
			}
		}
		int n = ++values[x2 + y2 * width];
		if (n == 2)
			++dangerCount;
	}

	void Print() {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				std::cout << values[x + y * width];
				if (x + 1 < width)
					std::cout << ",";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};

int main() {
	std::ifstream data("input_05_1.txt");
	if (!data.is_open()) return -1;

	Map map(1000, 1000);

	std::string input;
	while (data >> input) {
		int x1, y1, x2, y2;
		std::stringstream ss(input);
		ss >> x1;
		ss.ignore();
		ss >> y1;
		data >> input;
		data >> input;
		ss.clear();
		ss.str(input);
		ss >> x2;
		ss.ignore();
		ss >> y2;
		if (!(x1 == x2 || y1 == y2)) continue;
		map.Line(x1, y1, x2, y2);
	}

	std::cout << map.dangerCount;
	return 0;
}
