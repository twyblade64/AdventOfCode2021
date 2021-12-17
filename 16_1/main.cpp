#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Bitmap {
private:
	std::vector<unsigned int> data;
public:
	int Size() {
		return data.size() * sizeof(unsigned int) * 8;
	}

	void Write(unsigned int offset, unsigned int size, unsigned int value) {
		int cellSize = sizeof(unsigned int) * 8;
		int cellOffset = offset / cellSize;
		int bitOffset = offset % cellSize;
		for (int i = 0; i < size; ++i) {
			int cell = cellOffset + (bitOffset + size - 1 - i) / cellSize;
			while (data.size() <= cell) data.push_back((unsigned int) 0);
			unsigned int m = ((value >> i) & 1) << ((bitOffset + size - 1 - i) % cellSize);
			data[cell] = data[cell] & ~m | m;
		}
	}

	unsigned int Read(unsigned int offset, unsigned int size) {
		int cellSize = sizeof(unsigned int) * 8;
		unsigned int v = 0;
		int cellOffset = offset / cellSize;
		int bitOffset = offset % cellSize;
		for (int i = size - 1; i >= 0; --i) {
			int cell = cellOffset + (bitOffset + size - 1 - i) / cellSize;
			while (data.size() <= cell) data.push_back((unsigned int) 0);
			v = (v << 1) | ((data[cell] >> ((bitOffset + size - 1 - i) % cellSize)) & 1);
		}
		return v;
	}
};

int ReadPacket(Bitmap& bitmap, int pos, int depth, int& versionSum)
{
	std::cout << std::endl;
	for (int i = 0; i < depth; ++i)
		std::cout << "\t";
	int version = bitmap.Read(pos, 3); pos += 3;
	versionSum += version;
	std::cout << "-V: " << version;
	int id = bitmap.Read(pos, 3); pos += 3;
	std::cout << "\tT: " << id;
	if (id == 4) {
		unsigned int v = 0;
		unsigned char n;
		do {
			n = bitmap.Read(pos, 5); pos += 5;
			std::cout << "\tL:" << (n & 15);
			v = (v << 4) | (n&15);
		} while ((n & (1 << 4)) != 0);
		std::cout << "\tB:" << v;
	} else {
		int lengthType = bitmap.Read(pos, 1); pos += 1;
		std::cout << "\tI: " << lengthType;
		int lengthSize = lengthType == 0 ? 15 : 11;
		int lengthValue = bitmap.Read(pos, lengthSize); pos+= lengthSize;
		std::cout << "\tL: " << lengthValue;
		if (lengthType == 0)
		{
			int endPos = pos + lengthValue;
			while (pos < endPos)
			  	pos = ReadPacket(bitmap, pos, depth+1, versionSum);
		} else {
			for (int i = 0; i < lengthValue; ++i)
				pos = ReadPacket(bitmap, pos, depth+1, versionSum);
		}
	}
	return pos;
}

int main() {
	std::ifstream data("input_16_1.txt");
	if (!data.is_open()) return -1;

	Bitmap bitmap;

	int count = 0;
	char c;
	while (data >> c) {
		unsigned n = 0;
		if (c < 'A') n = c - '0';
		else n = c - 'A' + 10;
		bitmap.Write(count * 4, 4, n);
		++count;
	}

	int versionSum = 0;
	ReadPacket(bitmap, 0,0, versionSum);
	std::cout << std::endl << versionSum << std::endl;

	return 0;
}
