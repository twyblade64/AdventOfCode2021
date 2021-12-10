#include <iostream>
#include <fstream>
#include <vector>

int main() {
	std::ifstream data("input_09_1.txt");
	if (!data.is_open()) return -1;

	int width, height = 0;
	std::vector<int> map;

	std::string input;
	while (data >> input)
	{
		width = input.size();
		for (int i = 0; i < width; ++i)
			map.push_back(input[i] - '0');
		++height;
	}

	int sum = 0;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int flag = 10;
			int n = map[x + y * width];
			int up = y+1 < height ? map[x + (y+1) * width] : flag;
			int down = y > 0 ? map[x + (y-1) * width] : flag;
			int left = x > 0 ? map[(x-1) + y * width] : flag;
			int right = x + 1 < width ? map[(x+1) + y * width] : flag;
			if (n < up && n < down && n < left && n < right)
			{
				std::cout << "(" << x << "," << y << ")" << " " << n << std::endl;
				sum += n + 1;
			}
		}
	}

	std::cout << sum << std::endl;
	return 0;
}
