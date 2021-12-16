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
	std::ifstream data("input_15_1.txt");
	if (!data.is_open()) return -1;

	int width, height = 0;
	int mapWeights[256*256];
	int mapFrom[256*256];
	int mapLength[256*256];
	std::priority_queue<MapPath, std::vector<MapPath>, MapPathCompare> frontier;

	std::string line;
	while (std::getline(data, line))
	{
		width = line.size();
		for (int x = 0; x < width; ++x) {
			mapWeights[x + height * width] = (int) (line[x] - '0');
			mapFrom[x + height * width] = -1;
			mapLength[x + height * width] = std::numeric_limits<int>::max();
		}
		++height;
	}

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

	std::cout << width << " " << height << std::endl;
	std::cout << mapLength[(width-1) + (height-1) * width];

	return 0;
}
