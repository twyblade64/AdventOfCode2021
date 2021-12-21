#include <iostream>

int main() {
	int p1Pos = 8;
	int p2Pos = 7;
	int p1Score = 0;
	int p2Score = 0;
	int dice = 1;

	bool p1Turn = true;
	for (dice = 1; p1Score < 1000 && p2Score < 1000; dice += 3)
	{
		if (p1Turn) {
			p1Pos = (p1Pos - 1 + (dice) % 100 + (dice + 1) % 100 + (dice + 2) % 100) % 10 + 1;
			p1Score += p1Pos;
		} else {
			p2Pos = (p2Pos - 1 + (dice) % 100 + (dice + 1) % 100 + (dice + 2) % 100) % 10 + 1;
			p2Score += p2Pos;
		}
		p1Turn = !p1Turn;
	}

	std::cout << "P1: " << p1Score << std::endl;
	std::cout << "P2: " << p2Score << std::endl;
	std::cout << "Rolls: " << (dice-1) << std::endl;
	std::cout << "Answer: " << (p1Score < p2Score ? p1Score : p2Score) * (dice-1) << std::endl;

	return 0;
}
