#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

int main() {
	std::ifstream data("input_08_2.txt");
	if (!data.is_open()) return -1;

	std::string input;

	int sum = 0;
	char numbers[10];
	std::vector<int> sixes;
	while (data >> input)
	{
		sixes.clear();

		char a = 0x7F;
		char b = 0x7F;
		for (int i = 0; i < 10; ++i) {
			char n = 0;
			for (int j = 0; j < input.size(); ++j)
				n |= 1 << (input[j]-'a');
			switch(input.size())
			{
				case 2: numbers[1] = n; break;
				case 4: numbers[4] = n; break;
				case 3: numbers[7] = n; break;
				case 7: numbers[8] = n; break;
				case 5: a &= n; break;
				case 6: sixes.push_back(n); break;
			}
			data >> input;
		}
		numbers[9] = numbers[4] | a;
		numbers[3] = numbers[1] | a;
		numbers[0] = ~(numbers[4] & a) & 0x7F;
		for (int j = 0; j < 3; ++j)
		{
			if (sixes[j] != numbers[9] && sixes[j] != numbers[0]) {
				numbers[6] = sixes[j];
				break;
			}
		}
		numbers[5] = numbers[6] & numbers[9];
		numbers[2] = a | (~numbers[5] & 0x7F);

		int number = 0;
		for (int d = 0; d < 4; ++d)
		{
			data >> input;
			char n = 0;
			for (int j = 0; j < input.size(); ++j)
				n |= 1 << (input[j]-'a');
			for (int j = 0; j < 10; ++j)
			{
				if (n == numbers[j])
				{
					number = number * 10 + j;
					break;
				}
			}
		}
		std::cout << number << std::endl;
		sum += number;
	}

	std::cout << std::endl << sum << std::endl;

	return 0;
}
