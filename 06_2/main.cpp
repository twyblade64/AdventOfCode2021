#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
	std::ifstream data("input_06_2.txt");
	if (!data.is_open()) return -1;

	std::string input;
	data >> input;
	std::stringstream ss(input);

	long long int* bufferIn = new long long int[9];
	long long int* bufferOut = new long long int[9];
	for (int i = 0; i < 9; ++i)
		bufferIn[i] = 0;

	int n;
	while (ss >> n) {
		++bufferIn[n];
		ss.ignore();
	}

	int simulationDays = 256;
	for(int d = 0; d < simulationDays; ++d)
	{
		for (int i = 0; i < 8; ++i)
			bufferOut[i] = bufferIn[i+1];
		bufferOut[8] = bufferIn[0];
		bufferOut[6] += bufferIn[0];

		// Swap buffers
		long long int* temp = bufferIn;
		bufferIn = bufferOut;
		bufferOut = temp;
	}

	long long int sum = 0;
	for (int i = 0; i < 9; ++i)
		sum += bufferIn[i];

	delete[] bufferIn;
	delete[] bufferOut;

	std::cout << sum << std::endl;
	return 0;
}
