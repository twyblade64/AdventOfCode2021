#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <queue>
#include <cstring>
#include <unordered_set>
#include <limits>
#include <map>

const int TYPE_REQUIRED_ENERGY[4]{1,10,100,1000};

struct int2 {
public:
	int x;
	int y;
	int2() : x(0), y(0) {}
	int2(int x) : x(x), y(x) {}
	int2(int x, int y) : x(x), y(y) {}
	int2 &operator+=(int2 const &v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	int2 &operator-=(int2 const &v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
};
struct int2Hash {
	size_t operator()(const int2 &v) const { return std::hash<int>()(v.x | (v.y << 16)); }
};
inline bool operator==(int2 const &a, int2 const &b) { return (a.x == b.x) && (a.y == b.y); }
int2 operator+(int2 const &a, int2 const &b) { return int2(a.x + b.x, a.y + b.y); }
int2 operator-(int2 const &a, int2 const &b) { return int2(a.x - b.x, a.y - b.y); }

int abs(int n) {
	return n >= 0 ? n : -n;
}

void PrintPad(int n){
	for (int i = 0; i < n; ++i)
		std::cout << '-';
}

class State {
	int depth;
public:
	char *memory;
	char *slots[11];

	State(int depth) : depth(depth) {
		memory = new char[11+depth*4]{};
		int offset = 0;
		for (int i = 0; i < 11; ++i) {
			slots[i] = memory+offset;
			if (i >= 2 && i <= 8 && i % 2 == 0)
				offset += 1+depth;
			else
				offset += 1;
		}
	}

	State(const State &rhs) {
		depth = rhs.depth;
		memory = new char[11+depth*4];
		std::memcpy(memory, rhs.memory, sizeof(char) * (11+depth*4));
		int offset = 0;
		for (int i = 0; i < 11; ++i) {
			slots[i] = memory+offset;
			if (i >= 2 && i <= 8 && i % 2 == 0)
				offset += 1+depth;
			else
				offset += 1;
		}
	}

	State& operator=(const State& rhs) {
		depth = rhs.depth;
		memory = new char[11+depth*4];
		std::memcpy(memory, rhs.memory, sizeof(char) * (11+depth*4));
		int offset = 0;
		for (int i = 0; i < 11; ++i) {
			slots[i] = memory+offset;
			if (i >= 2 && i <= 8 && i % 2 == 0)
				offset += 1+depth;
			else
				offset += 1;
		}
	};

	~State() {
		delete[] memory;
	}

	void Swap(int fromX, int fromY, int toX, int toY) {
		int temp = slots[fromX][fromY];
		slots[fromX][fromY] = slots[toX][toY];
		slots[toX][toY] = temp;
	}

	int Depth() const {
		return depth;
	}

	void Print(int pad = 0) {
		char chars[6]{'#', '.', 'A', 'B', 'C', 'D'};
		for (int y = 0; y < depth+1; ++y) {
			PrintPad(pad);
			for (int x = 0; x < 11; ++x) {
				int n = -1;
				if (y == 0 || (x >= 2 && x <= 8 && x % 2 == 0))
					n = slots[x][y];
				std::cout << chars[n + 1];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	bool operator==(const State &other) {
		for (int i = 0; i < 11; ++i) {
			if (i >= 2 && i <= 8 && i % 2 == 0) {
				if (std::memcmp(slots[i], other.slots[i], sizeof(char)*(1+depth)) != 0)
					return false;
			} else {
				if (std::memcmp(slots[i], other.slots[i], sizeof(char)*(1)) != 0)
					return false;
			}
		}
		return true;
	}
};

class StateCompare
{
public:
	bool operator()(const State& a,const State& b)
	{
		for (int x = 0; x < 11; ++x) {
			int depth = (x >= 2 && x <= 8 && x % 2 == 0) ? a.Depth() + 1 : 1;
			for (int y = 0; y < depth; ++y)
			{
				if (a.slots[x][y] != b.slots[x][y])
					return a.slots[x][y] < b.slots[x][y];
			}
		}
		return false;
	}

	bool operator()(const std::pair<State, int>& a, const std::pair<State, int>& b)
	{
		return a.second > b.second;
	}
};

class MovementCommand {
public:
	int2 from;
	int2 to;
	int distance;

	MovementCommand(int2 from, int2 to, int distance) : from(from), to(to), distance(distance) {}
};

bool MovementAvailable(State& currentState, int fromX, int toX) {
	int dX = fromX < toX ? 1 : -1;
	if (currentState.slots[toX][0] != 0)
		return false;
	for (int x = fromX+dX; x != toX; x += dX)
		if (currentState.slots[x][0] != 0)
			return false;
	return true;
}


bool IsValidState(State& currentState) {
	for (int x = 3; x <= 5; x+=2) {
		if (currentState.slots[x][0] != 0){
			int targetX = currentState.slots[x][0] * 2;
			for (int otherX = x+2; otherX <= 7; otherX+=2) {
				if (currentState.slots[otherX][0] != 0) {
					int otherTargetX = currentState.slots[otherX][0] * 2;
					if (targetX > otherX && otherTargetX < x)
						return false;
				}
			}
		}
	}
	 return true;
}

bool IsEndReached(State &currentState) {
	for (int type = 1; type < 5; ++type)
		for (int depth = currentState.Depth(); depth >= 1; --depth)
			if (currentState.slots[type * 2][depth] != type)
				return false;
	return true;
}

std::vector<MovementCommand> GetAvailableMovements(State& currentState){
	std::vector<MovementCommand> availableMovements;
	bool pitFillable[4]{};
	int pitDepth[4]{};
	for (int type = 1; type < 5; ++type) {
		bool fillable = true;
		int depth;
		for (depth = currentState.Depth(); depth >= 1; --depth) {
			if (currentState.slots[type * 2][depth] == 0)
				break;
			fillable &= currentState.slots[type * 2][depth] == type || currentState.slots[type * 2][depth] == 0;
		}
		pitFillable[type - 1] = fillable;
		pitDepth[type - 1] = depth;
	}

	// Pit To Pit
	for (int typePit = 1; typePit < 5; ++typePit) {
		if(pitDepth[typePit - 1] != currentState.Depth() && !pitFillable[typePit-1])
		{
			int type = currentState.slots[typePit*2][pitDepth[typePit - 1]+1];
			if (type != typePit &&
			pitFillable[type-1] &&
			pitDepth[type - 1] != 0 &&
			MovementAvailable(currentState, typePit*2, type*2)){
				availableMovements.push_back(MovementCommand(int2(typePit * 2, pitDepth[typePit - 1] + 1),int2(type*2, pitDepth[type - 1]), abs(typePit*2 - type*2) + pitDepth[typePit - 1] + 1 + pitDepth[type - 1]));
				return availableMovements;
			}
		}
	}

	// Hallway ampiphods to pits
	for (int x = 0; x < 11; ++x) {
		int type = currentState.slots[x][0];
		if (type != 0 &&
			pitFillable[type - 1] &&
			pitDepth[type - 1] != 0 &&
			MovementAvailable(currentState, x, type * 2)) {
			availableMovements.push_back(MovementCommand(int2(x, 0), int2(type * 2, pitDepth[type - 1]), abs(type * 2 - x) + pitDepth[type - 1]));
		}
	}

	// Pit To hallway
	for (int typePit = 1; typePit < 5; ++typePit) {

		if (!pitFillable[typePit - 1] && pitDepth[typePit - 1] != currentState.Depth()) {
			for (int x = 0; x < 11; ++x) {
				if (x >= 2 && x <= 8 && x % 2 == 0)
					continue;
				if (MovementAvailable(currentState, typePit * 2, x)) {
					availableMovements.push_back(MovementCommand(int2(typePit * 2, pitDepth[typePit - 1] + 1),int2(x, 0), abs(typePit * 2 - x) + pitDepth[typePit - 1] + 1));
				}
			}
		}
	}

	return availableMovements;
}

void DijkstraSearch(State& startState, int accumulatedEnergy, int& minimumEnergy, int& checks, int d = 0){
	std::map<State, int, StateCompare> stateEnergy;
	std::priority_queue<std::pair<State, int>, std::vector<std::pair<State, int>>, StateCompare> frontier;

	stateEnergy.emplace(startState, 0);
	frontier.push(std::pair<State, int>(startState, 0));

	while(!frontier.empty()) {
		auto pair = frontier.top();
		frontier.pop();
		State& currentState = pair.first;
		int accumulatedEnergy = pair.second;

		if (stateEnergy.find(currentState)->second < accumulatedEnergy)
			continue;

		++checks;
		// std::cout << checks << " " << accumulatedEnergy << std::endl;
		// std::cout << accumulatedEnergy << std::endl;
		// currentState.Print();

		if (IsEndReached(currentState)) {
			std::cout << "---- Required energy: " << accumulatedEnergy << std::endl<< std::endl;
			if (accumulatedEnergy < minimumEnergy)
				minimumEnergy = accumulatedEnergy;
			return;
		}

		auto movements = GetAvailableMovements(currentState);
		for (int i = 0; i < movements.size(); ++i)
		{
			auto movement = movements[i];
			int type = currentState.slots[movement.from.x][movement.from.y];
			int requiredEnergy = movement.distance * TYPE_REQUIRED_ENERGY[type - 1];
			if (accumulatedEnergy + requiredEnergy < minimumEnergy) {
				State nextState(currentState);
				nextState.Swap(movement.from.x, movement.from.y, movement.to.x, movement.to.y);
				if (IsValidState(nextState)) {
					auto index = stateEnergy.find(nextState);
					if (index == stateEnergy.end()) {
						stateEnergy.emplace(nextState, accumulatedEnergy + requiredEnergy);
					} else{
						if (index->second < accumulatedEnergy + requiredEnergy)
							continue;
						index->second = accumulatedEnergy + requiredEnergy;
					}
					frontier.push(std::pair<State, int>(nextState, accumulatedEnergy + requiredEnergy));
				}
			}
		}
	}
}

int main() {
	std::ifstream data("input_23_2.txt");
	if (!data.is_open()) return -1;

	State startState(4);
	std::string line;
	for (int y = 0; std::getline(data, line); ++y) {
		for (int x = 0; x < line.size(); ++x) {
			switch (line[x]) {
				case 'A': startState.slots[x-1][y-1] = 1; break;
				case 'B': startState.slots[x-1][y-1] = 2; break;
				case 'C': startState.slots[x-1][y-1] = 3; break;
				case 'D': startState.slots[x-1][y-1] = 4; break;
			}
		}
	}

	int checks = 0;
	int minimumEnergy = std::numeric_limits<int>::max();
	DijkstraSearch(startState, 0, minimumEnergy, checks);

	std::cout << "Checks: " << checks << std::endl;
	std::cout << "Minimum energy: " << minimumEnergy << std::endl;
	return 0;
}
