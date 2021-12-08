#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream data("input_08_1.txt");
	if (!data.is_open()) return -1;

	int count[10] {0,0,0,0,0,0,0,0,0,0};
	std::string input;
	while (data >> input)
	{
		for (int i = 0; i < 10; ++i)
			data >> input;
		for (int i = 0; i < 4; ++i)
		{
			data >> input;
			switch (input.length())
			{
				case 2: ++count[1]; break;
				case 3: ++count[7]; break;
				case 4: ++count[4]; break;
				case 7: ++count[8]; break;
			}
		}
	}

	int sum = 0;
	for (int i = 0; i < 10; ++i) {
		std::cout << count[i] << " ";
		sum += count[i];
	}
	std::cout << std::endl << sum << std::endl;

	return 0;
}
