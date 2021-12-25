#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class ALU_Op {
public:
	enum CODE {
		INP, ADD, RADD, MUL, RMUL, DIV, RDIV, MOD, RMOD, EQL, REQL
	};

	CODE code;
	int a;
	int b;

	ALU_Op(CODE code, int a) : code(code), a(a), b(0) {}

	ALU_Op(CODE code, int a, int b) : code(code), a(a), b(b) {}
};

class ALU {
public:


	int *memory;
	long long int registers[4];
	std::vector<ALU_Op> program;

	void Execute() {
		int memOffset = 0;
		for (int i = 0; i < program.size(); ++i) {
			ALU_Op op = program[i];
			switch (op.code) {
				case ALU_Op::INP: // inp a
					Print();
					registers[op.a] = memory[memOffset];
					++memOffset;
					break;
				case ALU_Op::ADD: // add a b
					registers[op.a] = registers[op.a] + op.b;
					break;
				case ALU_Op::RADD: // radd a b
					registers[op.a] = registers[op.a] + registers[op.b];
					break;
				case ALU_Op::MUL: // mul a b
					registers[op.a] = registers[op.a] * op.b;
					break;
				case ALU_Op::RMUL: // rmul a b
					registers[op.a] = registers[op.a] * registers[op.b];
					break;
				case ALU_Op::DIV: // div a b
					registers[op.a] = registers[op.a] / op.b;
					break;
				case ALU_Op::RDIV: // rdiv a b
					registers[op.a] = registers[op.a] / registers[op.b];
					break;
				case ALU_Op::MOD: // mod a b
					registers[op.a] = registers[op.a] % op.b;
					break;
				case ALU_Op::RMOD: // rmod a b
					registers[op.a] = registers[op.a] % registers[op.b];
					break;
				case ALU_Op::EQL: // eql a b
					registers[op.a] = registers[op.a] == op.b ? 1 : 0;
					break;
				case ALU_Op::REQL: // reql a b
					registers[op.a] = registers[op.a] == registers[op.b] ? 1 : 0;
					break;
			}
		}
	}

	void Reset() {
		for (int i = 0; i < 4; ++i)
			registers[i] = 0;
	}

	void Print() {
		std::cout << "w: " << registers[0] << "\t";
		std::cout << "x: " << registers[1] << "\t";
		std::cout << "y: " << registers[2] << "\t";
		std::cout << "z: " << registers[3] << std::endl;
	}
};

int stoi(const std::string &s) {
	int n = 0;
	bool positive = true;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '-') positive = false;
		else n = n * 10 + s[i] - '0';
	}
	return positive ? n : -n;
}

void ReadALUProgram(ALU &alu) {
	std::ifstream data("input_24_1.txt");
	if (!data.is_open()) return;

	std::string input;
	while (data >> input) {
		if (input.compare("inp") == 0) {
			int a, b;
			data >> input;
			a = input[0] - 'w';
			alu.program.push_back(ALU_Op(ALU_Op::INP, a));
		}

		if (input.compare("add") == 0) {
			int a, b;
			data >> input;
			a = input[0] - 'w';
			data >> input;
			if (input[0] - 'w' >= 0) {
				b = input[0] - 'w';
				alu.program.push_back(ALU_Op(ALU_Op::RADD, a, b));
			} else {
				b = stoi(input);
				alu.program.push_back(ALU_Op(ALU_Op::ADD, a, b));
			}
		}

		if (input.compare("mul") == 0) {
			int a, b;
			data >> input;
			a = input[0] - 'w';
			data >> input;
			if (input[0] - 'w' >= 0) {
				b = input[0] - 'w';
				alu.program.push_back(ALU_Op(ALU_Op::RMUL, a, b));
			} else {
				b = stoi(input);
				alu.program.push_back(ALU_Op(ALU_Op::MUL, a, b));
			}
		}

		if (input.compare("div") == 0) {
			int a, b;
			data >> input;
			a = input[0] - 'w';
			data >> input;
			if (input[0] - 'w' >= 0) {
				b = input[0] - 'w';
				alu.program.push_back(ALU_Op(ALU_Op::RDIV, a, b));
			} else {
				b = stoi(input);
				alu.program.push_back(ALU_Op(ALU_Op::DIV, a, b));
			}
		}

		if (input.compare("mod") == 0) {
			int a, b;
			data >> input;
			a = input[0] - 'w';
			data >> input;
			if (input[0] - 'w' >= 0) {
				b = input[0] - 'w';
				alu.program.push_back(ALU_Op(ALU_Op::RMOD, a, b));
			} else {
				b = stoi(input);
				alu.program.push_back(ALU_Op(ALU_Op::MOD, a, b));
			}
		}

		if (input.compare("eql") == 0) {
			int a, b;
			data >> input;
			a = input[0] - 'w';
			data >> input;
			if (input[0] - 'w' >= 0) {
				b = input[0] - 'w';
				alu.program.push_back(ALU_Op(ALU_Op::REQL, a, b));
			} else {
				b = stoi(input);
				alu.program.push_back(ALU_Op(ALU_Op::EQL, a, b));
			}
		}
	}
}

int main() {
	ALU alu;
	ReadALUProgram(alu);

	int memory[14]{2,9,9,9,1,9,9,3,6,9,8,4,6,9};
	alu.memory = memory;

	alu.Reset();
	alu.Execute();
	alu.Print();

	return 0;
}
