#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

class Bitmap {
private:
	std::vector<unsigned long long int> data;
public:
	int Size() {
		return data.size() * sizeof(unsigned long long int) * 8;
	}

	void Write(unsigned long long int offset, unsigned long long int size, unsigned long long int value) {
		int cellSize = sizeof(unsigned long long int) * 8;
		int cellOffset = offset / cellSize;
		int bitOffset = offset % cellSize;
		for (int i = 0; i < size; ++i) {
			int cell = cellOffset + (bitOffset + size - 1 - i) / cellSize;
			while (data.size() <= cell) data.push_back((unsigned long long int) 0);
			unsigned long long int m = ((value >> i) & 1) << ((bitOffset + size - 1 - i) % cellSize);
			data[cell] = data[cell] & ~m | m;
		}
	}

	unsigned long long int Read(unsigned long long int offset, unsigned long long int size) {
		int cellSize = sizeof(unsigned long long int) * 8;
		unsigned long long int v = 0;
		int cellOffset = offset / cellSize;
		int bitOffset = offset % cellSize;
		for (int i = size - 1; i >= 0; --i) {
			int cell = cellOffset + (bitOffset + size - 1 - i) / cellSize;
			while (data.size() <= cell) data.push_back((unsigned long long int) 0);
			v = (v << 1) | ((data[cell] >> ((bitOffset + size - 1 - i) % cellSize)) & 1);
		}
		return v;
	}
};

int ReadPacket(Bitmap& bitmap, int pos, int depth, unsigned long long int& value)
{
	std::cout << std::endl;
	for (int i = 0; i < depth; ++i)
		std::cout << " ";
	int version = bitmap.Read(pos, 3); pos += 3;
	// std::cout << "-V: " << version;
	int id = bitmap.Read(pos, 3); pos += 3;
	// std::cout << "\tT: " << id;
	if (id == 4) {
		unsigned long long int v = 0;
		unsigned char n;
		do {
			n = bitmap.Read(pos, 5); pos += 5;
			// std::cout << "\tL:" << (n & 15);
			v = (v << 4) | (n&15);
		} while ((n & (1 << 4)) != 0);
		value = v;
		std::cout << v;
	} else {
		int lengthType = bitmap.Read(pos, 1); pos += 1;
		// std::cout << "\tI: " << lengthType;
		int lengthSize = lengthType == 0 ? 15 : 11;
		int lengthValue = bitmap.Read(pos, lengthSize); pos+= lengthSize;
		// std::cout << "\tL: " << lengthValue;
		std::vector<unsigned long long int> subValues;

		switch(id)
		{
			case 0: std::cout << "+"; break;
			case 1: std::cout << "*"; break;
			case 2: std::cout << "min"; break;
			case 3: std::cout << "max"; break;
			case 5: std::cout << ">"; break;
			case 6: std::cout << "<"; break;
			case 7: std::cout << "="; break;
		}

		if (lengthType == 0)
		{
			int endPos = pos + lengthValue;
			while (pos < endPos) {
				subValues.push_back(0);
				pos = ReadPacket(bitmap, pos, depth + 1, subValues[subValues.size() - 1]);
			}
		} else {
			for (int i = 0; i < lengthValue; ++i) {
				subValues.push_back(0);
				pos = ReadPacket(bitmap, pos, depth + 1, subValues[subValues.size() - 1]);
			}
		}

		switch(id)
		{
			case 0:

				value = 0;
				for (int i = 0; i < subValues.size(); ++i)
					value += subValues[i];
				break;
			case 1:
				value = 1;
				for (int i = 0; i < subValues.size(); ++i)
					value *= subValues[i];
				break;
			case 2:
				value = std::numeric_limits<unsigned long long int>::max();
				for (int i = 0; i < subValues.size(); ++i)
					value = subValues[i] < value ? subValues[i] : value;
				break;
			case 3:
				value = std::numeric_limits<unsigned long long int>::min();
				for (int i = 0; i < subValues.size(); ++i)
					value = subValues[i] > value ? subValues[i] : value;
				break;
			case 5:
				value = subValues[0] > subValues[1] ? 1 : 0;
				break;
			case 6:
				value = subValues[0] < subValues[1] ? 1 : 0;
				break;
			case 7:
				value = subValues[0] == subValues[1] ? 1 : 0;
				break;
		}
	}
	return pos;
}

int main() {
	std::ifstream data("input_16_2.txt");
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

	unsigned long long int value = 0;
	ReadPacket(bitmap, 0,0, value);
	std::cout << std::endl << value << std::endl;

	return 0;
}
