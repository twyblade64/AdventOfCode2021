#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

int main() {
	std::ifstream data("input_09_2.txt");
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

	int smallestIndex = 0;
	int largest[3]{0,0,0};
	std::stack<int> pendingCells;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (map[x + y * width]!= 9){
				int size = 0;
				pendingCells.push(x + y * width);
				while (!pendingCells.empty()) {
					int pos = pendingCells.top();
					pendingCells.pop();
					if (map[pos] != 9) {
						++size;
						map[pos] = 9;
						int x = pos % width;
						int y = pos / width;
						if (x - 1 >= 0) pendingCells.push((x - 1) + y * width);
						if (x + 1 < width) pendingCells.push((x + 1) + y * width);
						if (y - 1 >= 0) pendingCells.push(x + (y - 1) * width);
						if (y + 1 < height) pendingCells.push(x + (y + 1) * width);
					}
				}
				std::cout << " " << size << std::endl;
				if (size > largest[smallestIndex]) {
					largest[smallestIndex] = size;
					smallestIndex = 0;
					int smallestValue = largest[smallestIndex];
					for (int i = 1; i < 3; ++i)
					{
						if (largest[i] < smallestValue)
						{
							smallestIndex = i;
							smallestValue = largest[smallestIndex];
						}
					}
				}
			}
		}
	}

	int mul = 1;
	for (int i = 0; i < 3; ++i)
		mul *= largest[i];
	std::cout << mul << std::endl;
	return 0;
}
