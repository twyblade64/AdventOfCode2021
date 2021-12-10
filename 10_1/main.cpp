#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

int main() {
	std::ifstream data("input_10_1.txt");
	if (!data.is_open()) return -1;

	int sum = 0;
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
					if (stack.top() != '(') {
						sum += 3;
						corrupt = true;
					} else {
						stack.pop();
					}
					break;
				case ']':
					if (stack.top() != '[') {
						sum += 57;
						corrupt = true;
					} else {
						stack.pop();
					}
					break;
				case '}':
					if (stack.top() != '{') {
						sum += 1197;
						corrupt = true;
					} else {
						stack.pop();
					}
					break;
				case '>':
					if (stack.top() != '<') {
						sum += 25137;
						corrupt = true;
					} else {
						stack.pop();
					}
					break;
			}
		}
	}

	std::cout << sum << std::endl;
	return 0;
}
