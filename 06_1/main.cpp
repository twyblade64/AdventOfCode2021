#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
	std::ifstream data("input_06_1.txt");
	if (!data.is_open()) return -1;

	std::string input;
	data >> input;
	std::stringstream ss(input);

	std::vector<int> fishes;
	int n;
	while (ss >> n) {
		fishes.push_back(n);
		ss.ignore();
	}

	int simulationDays = 80;
	for(int d = 0; d < simulationDays; ++d)
	{
		for (int i = 0, n = fishes.size(); i < n; ++i){
			if (--fishes[i] < 0) {
				fishes[i] = 6;
				fishes.push_back(8);
			}
		}
	}

	std::cout << fishes.size() << std::endl;
	return 0;
}
