#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Region3 {
public:
	int xMin, xMax;
	int yMin, yMax;
	int zMin, zMax;

	Region3() : xMin(0), xMax(0), yMin(0), yMax(0), zMin(0), zMax(0) {}

	Region3(int xMin, int xMax, int yMin, int yMax, int zMin, int zMax) :
			xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax), zMin(zMin), zMax(zMax) {}

	long long int Volume() {
		return (long long int)(xMax - xMin) * (yMax - yMin) * (zMax - zMin);
	}
};

int Abs(int n) {
	return n >= 0 ? n : -n;
}

int Min(int a, int b) {
	return a < b ? a : b;
}

int Max(int a, int b) {
	return a > b ? a : b;
}

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

bool IsRegionOverlap(Region3 a, Region3 b) {
	return (Abs((a.xMax + a.xMin) - (b.xMax + b.xMin)) - ((a.xMax - a.xMin) + (b.xMax - b.xMin)) < 0) &&
		   (Abs((a.yMax + a.yMin) - (b.yMax + b.yMin)) - ((a.yMax - a.yMin) + (b.yMax - b.yMin)) < 0) &&
		   (Abs((a.zMax + a.zMin) - (b.zMax + b.zMin)) - ((a.zMax - a.zMin) + (b.zMax - b.zMin)) < 0);
}

std::vector<Region3> GetRemovalRegions(Region3 base, Region3 remove) {
	std::vector<Region3> regions;
	int xP[4]{};
	int yP[4]{};
	int zP[4]{};

	xP[0] = base.xMin;
	xP[1] = Max(base.xMin, remove.xMin);
	xP[2] = Min(base.xMax, remove.xMax);
	xP[3] = base.xMax;
	yP[0] = base.yMin;
	yP[1] = Max(base.yMin, remove.yMin);
	yP[2] = Min(base.yMax, remove.yMax);
	yP[3] = base.yMax;
	zP[0] = base.zMin;
	zP[1] = Max(base.zMin, remove.zMin);
	zP[2] = Min(base.zMax, remove.zMax);
	zP[3] = base.zMax;

	for (int i = 0; i < 3 * 3 * 3; ++i) {
		if (i == 13)
			continue;
		int x = i % 3;
		int y = i / 3 % 3;
		int z = i / 9;
		Region3 region(xP[x], xP[x + 1], yP[y], yP[y + 1], zP[z], zP[z + 1]);
		if (region.Volume() > 0)
			regions.push_back(region);
	}
	return regions;
}

void RemoveRegion(std::vector<Region3> &regions, Region3 targetRegion) {
	std::vector<int> removedRegionsIndex;
	std::vector<Region3> addedRegions;

	for (int i = 0; i < regions.size(); ++i) {
		auto &region = regions[i];
		if (IsRegionOverlap(targetRegion, region)) {
			std::vector<Region3> newRegions = GetRemovalRegions(region, targetRegion);
			for (int i = 0; i < newRegions.size(); ++i)
				addedRegions.push_back(newRegions[i]);
			removedRegionsIndex.push_back(i);
		}
	}

	for (int i = removedRegionsIndex.size() - 1; i >= 0; --i)
		regions.erase(regions.begin() + removedRegionsIndex[i]);

	for (int i = 0; i < addedRegions.size(); ++i)
		regions.push_back(addedRegions[i]);
}

void AddRegion(std::vector<Region3> &regions, Region3 targetRegion) {
	RemoveRegion(regions, targetRegion);
	regions.push_back(targetRegion);
}

int main() {
	std::ifstream data("input_22_2.txt");
	if (!data.is_open()) return -1;

	std::vector<Region3> regions;
	std::string line;
	while (data >> line) {
		bool on = line.compare("on") == 0;
		int minX, minY, minZ, maxX, maxY, maxZ;
		int parsePosition = 0;
		data >> line;
		minX = ExtractInteger(line, parsePosition);
		maxX = ExtractInteger(line, parsePosition)+1;
		minY = ExtractInteger(line, parsePosition);
		maxY = ExtractInteger(line, parsePosition)+1;
		minZ = ExtractInteger(line, parsePosition);
		maxZ = ExtractInteger(line, parsePosition)+1;

		Region3 region(minX, maxX, minY, maxY, minZ, maxZ);
		if (on)
			AddRegion(regions, region);
		else
			RemoveRegion(regions, region);

		long long int count = 0;
		for (int i = 0; i < regions.size(); ++i)
			count += regions[i].Volume();
		std::cout << count << std::endl;
	}
	return 0;
}
