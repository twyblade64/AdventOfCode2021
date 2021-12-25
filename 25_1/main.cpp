#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

const char PRINT_CHARS[3] {'.','>','v'};

enum class Dir : char {
	Empty,
	Right,
	Down
};

void SwapPointers(Dir*& a, Dir*& b){
	Dir* temp = a;
	a = b;
	b = temp;
}

int main() {
	std::ifstream data("input_25_1.txt");
	if (!data.is_open()) return -1;

	Dir* mapRead = new Dir[140*140]{};
	Dir* mapWrite = new Dir[140*140]{};

	int width = 0;
	int height = 0;
	std::string line;
	while (std::getline(data, line))
	{
		width = line.size();
		for (int x = 0; x < width; ++x)
		{
			switch (line[x]){
				case '.' : mapRead[x + height * width] = Dir::Empty; break;
				case '>' : mapRead[x + height * width] = Dir::Right; break;
				case 'v' : mapRead[x + height * width] = Dir::Down; break;
			}
			mapWrite[x + height * width] = Dir::Empty;
		}
		++height;
	}

	int steps = 0;
	bool moving = true;
	while (moving) {
		moving = false;

		// East step
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				if (mapRead[x+y*width] == Dir::Right)
				{
					if (mapRead[(x+1)%width + y*width] == Dir::Empty)
					{
						mapWrite[(x+1)%width + y*width] = Dir::Right;
						moving = true;
					} else {
						mapWrite[x + y*width] = Dir::Right;
					}
				}
				if (mapRead[x+y*width] == Dir::Down)
					mapWrite[x+y*width] = Dir::Down;
			}
		}

		SwapPointers(mapRead, mapWrite);
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x)
				mapWrite[x + y * width] = Dir::Empty;

		// South step
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				if (mapRead[x+y*width] == Dir::Down)
				{
					if (mapRead[x + ((y+1)%height)*width] == Dir::Empty)
					{
						mapWrite[x + ((y+1)%height)*width] = Dir::Down;
						moving = true;
					} else {
						mapWrite[x + y*width] = Dir::Down;
					}
				}
				if (mapRead[x+y*width] == Dir::Right)
					mapWrite[x+y*width] = Dir::Right;
			}
		}

		SwapPointers(mapRead, mapWrite);
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x)
				mapWrite[x + y * width] = Dir::Empty;

		++steps;
	}

	std::cout << "Steps passed: " << steps << std::endl;

	return 0;
}
