#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <limits>

class MapPath
{
public:
	int pos;
	int length;
	MapPath(int pos, int length) : pos(pos), length(length) {}
};

class MapPathCompare
{
public:
	bool operator()(MapPath a, MapPath b)
	{
		return a.length > b.length;
	}
};

int main() {
	std::ifstream data("input_15_2.txt");
	if (!data.is_open()) return -1;

	int width, height = 0;
	std::vector<int> mapWeightsBase(512*512);
	std::vector<int> mapWeights(512*512);
	std::vector<int> mapFrom(512*512);
	std::vector<int> mapLength(512*512);
	std::priority_queue<MapPath, std::vector<MapPath>, MapPathCompare> frontier;

	std::string line;
	while (std::getline(data, line))
	{
		width = line.size();
		for (int x = 0; x < width; ++x)
			mapWeightsBase[x + height * width] = (int) (line[x] - '0');
		++height;
	}

	for (int y = 0; y < width; ++y)
	{
		for (int x = 0; x < height; ++x)
		{
			for (int rY = 0; rY < 5; ++rY) {
				for (int rX = 0; rX < 5; ++rX) {
					mapWeights[(x+rX * width) + (y+rY*height) * width*5] = (mapWeightsBase[x + y * width] + rX + rY - 1) % 9 + 1;
					mapFrom[(x+rX * width) + (y+rY*height) * width*5] = -1;
					mapLength[(x+rX * width) + (y+rY*height) * width*5] = std::numeric_limits<int>::max();
				}
			}
		}
	}
	height *=5;
	width *=5;

	mapFrom[0] = 0;
	mapLength[0] = 0;
	frontier.push(MapPath(0,0));

	while(!frontier.empty())
	{
		auto path = frontier.top();
		frontier.pop();

		int x = path.pos % width;
		int y = path.pos / width;
		for (int i = 0; i < 4; ++i)
		{
			int pX = x+ (1-i/2) * (i%2*2-1);
			int pY = y+(i/2) * (i%2*2-1);
			if (pX < 0 || pX >= width || pY < 0 || pY >= height) continue;
			int newLength = path.length + mapWeights[pX + pY * width];
			if (newLength < mapLength[pX + pY * width])
			{
				mapLength[pX + pY * width] = newLength;
				frontier.push(MapPath(pX + pY*width, newLength));
			}
		}
	}

	// for (int y = 0; y < height; ++y)
	// {
	// 	for (int x = 0; x < width; ++x)
	// 		std::cout << mapWeights[x + y * width];
	// 	std::cout << std::endl;
	// }

	std::cout << mapLength[(width-1) + (height-1) * width];

	return 0;
}
