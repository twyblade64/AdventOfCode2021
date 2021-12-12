#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <memory>

int main() {
	std::ifstream data("input_12_2.txt");
	if (!data.is_open()) return -1;

	std::map<std::string, std::unique_ptr<std::vector<std::string>>> transitions;
	std::map<std::string, int> passes;
	std::stack<std::string> pathNode;
	std::stack<int> pathTransition;
	int pathCount = 0;
	bool smallCaveVisitedTwice = false;

	// Create transitions
	std::string input;
	while (data >> input) {
		int delimiter = input.find('-');
		std::string a = input.substr(0, delimiter);
		std::string b = input.substr(delimiter + 1);

		if (transitions.find(a) == transitions.end())
			transitions.emplace(a, std::unique_ptr<std::vector<std::string>>(
					new std::vector<std::string>));
		if (transitions.find(b) == transitions.end())
			transitions.emplace(b, std::unique_ptr<std::vector<std::string>>(
					new std::vector<std::string>));
		if (b.compare("start") != 0 && a.compare("end") != 0) transitions[a]->push_back(b);
		if (a.compare("start") != 0 && b.compare("end") != 0) transitions[b]->push_back(a);
	}

	// Create passes map
	for (auto &keyVal: transitions)
		passes.emplace(keyVal.first, 0);

	// Depth first search
	pathNode.push("start");
	pathTransition.push(-1);
	++passes["start"];
	while (!pathNode.empty()) {
		std::string node = pathNode.top();
		if (node.compare("end") != 0) {
			++pathTransition.top();
			bool transitionSelected = false;
			while (!transitionSelected && pathTransition.top() < transitions[node]->size()) {
				std::string nextNode = transitions[node]->at(pathTransition.top());
				if (nextNode[0] < 'a' || passes[nextNode] == 0 || (!smallCaveVisitedTwice && passes[nextNode] == 1)) {
					if (!(nextNode[0] < 'a') && passes[nextNode] == 1)
						smallCaveVisitedTwice = true;
					transitionSelected = true;
					++passes[nextNode];
					pathNode.push(nextNode);
					pathTransition.push(-1);
				} else {
					++pathTransition.top();
				}
			}

			if (!transitionSelected) {
				if (!(pathNode.top()[0] < 'a') && passes[pathNode.top()] > 1)
					smallCaveVisitedTwice = false;
				--passes[pathNode.top()];
				pathNode.pop();
				pathTransition.pop();
			}
		} else {
			// Printing takes too long
			// std::stack<std::string> debugStack;
			// while (!pathNode.empty()) {
			// 	debugStack.push(pathNode.top());
			// 	pathNode.pop();
			// }
			// while (!debugStack.empty()) {
			// 	std::cout << debugStack.top();
			// 	pathNode.push(debugStack.top());
			// 	debugStack.pop();
			// 	if (!debugStack.empty())
			// 		std::cout << ",";
			// }
			// std::cout << std::endl;

			++pathCount;
			--passes[pathNode.top()];
			pathNode.pop();
			pathTransition.pop();
		}
	}

	std::cout << pathCount << std::endl;

	return 0;
}
