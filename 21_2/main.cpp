#include <iostream>
#include <map>

#define GameResults std::pair<long long int, long long int>

inline GameResults operator+(const GameResults &lhs, const GameResults &rhs) {
	return GameResults(lhs.first + rhs.first, lhs.second + rhs.second);
}

int GetStateNumber(int p1Pos, int p2Pos, int p1Score, int p2Score, bool p1Turn) {
	return
			p1Pos * 10 * 21 * 21 * 2 +
			p2Pos * 21 * 21 * 2 +
			p1Score * 21 * 2 +
			p2Score * 2 +
			(p1Turn ? 0 : 1);
}

GameResults GetGameResults(std::map<int, GameResults>& cachedResults, int p1Pos, int p2Pos, int p1Score, int p2Score, bool p1Turn) {
	int stateNumber = GetStateNumber(p1Pos, p2Pos, p1Score, p2Score, p1Turn);
	if (cachedResults.find(stateNumber) != cachedResults.end())
		return cachedResults[stateNumber];
	if (p1Score >= 21) return GameResults(1,0);
	if (p2Score >= 21) return GameResults(0,1);
	GameResults results(0,0);
	for (int r1 = 1; r1 <= 3; ++r1)
		for (int r2 = 1; r2 <= 3; ++r2)
			for (int r3 = 1; r3 <= 3; ++r3)
				results = results + GetGameResults(cachedResults,
												   p1Turn ? (p1Pos + r1 + r2 + r3) % 10 : p1Pos,
												   !p1Turn ? (p2Pos + r1 + r2 + r3) % 10 : p2Pos,
												   p1Turn ? p1Score + (p1Pos + r1 + r2 + r3) % 10 + 1 : p1Score,
												   !p1Turn ? p2Score + (p2Pos + r1 + r2 + r3) % 10 + 1 : p2Score,
												   !p1Turn);
	cachedResults[stateNumber] = results;
	return cachedResults[stateNumber];
}

int main() {
	std::map<int, GameResults > cachedResults;
	GameResults gameResults = GetGameResults(cachedResults, 8-1, 7-1, 0, 0, true);
	std::cout << "Results: " << gameResults.first << " " << gameResults.second << std::endl;
	std::cout << "Winner: " << (gameResults.first > gameResults.second ? "P1" : "P2") << " " << (gameResults.first > gameResults.second ? gameResults.first : gameResults.second) << std::endl;

	return 0;
}
