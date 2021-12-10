#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

int main() {
	std::ifstream data("input_10_2.txt");
	if (!data.is_open()) return -1;

	std::vector<long long int> sums;
	std::stack<char> stack;
	std::string input;
	while (data >> input) {
		bool corrupt = false;
		while (!stack.empty()) stack.pop();
		for (int i = 0; i < input.size() && !corrupt; ++i) {
			switch (input[i]) {
				case '(':
				case '[':
				case '{':
				case '<':
					stack.push(input[i]);
					break;
				case ')':
					if (stack.top() != '(') corrupt = true;
					else stack.pop();
					break;
				case ']':
					if (stack.top() != '[') corrupt = true;
					else stack.pop();
					break;
				case '}':
					if (stack.top() != '{') corrupt = true;
					else stack.pop();
					break;
				case '>':
					if (stack.top() != '<') corrupt = true;
					else stack.pop();
					break;
			}
		}

		long long int sum = 0;
		if (!corrupt) {
			while (!stack.empty()){
				switch(stack.top())
				{
					case '(': sum = sum*5 +1; break;
					case '[': sum = sum*5 +2; break;
					case '{': sum = sum*5 +3; break;
					case '<': sum = sum*5 +4; break;
				}
				stack.pop();
			}
			sums.push_back(sum);
		}
	}

	std::sort(sums.begin(), sums.end());
	std::cout << sums[sums.size()/2] << std::endl;
	return 0;
}
