#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Vector3 {
public:
	int x, y, z;

	Vector3() : x(0), y(0), z(0) {}

	Vector3(int x) : x(x), y(x), z(x) {}

	Vector3(int x, int y, int z) : x(x), y(y), z(z) {}

	Vector3 &operator+=(Vector3 const &v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3 &operator-=(Vector3 const &v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	bool operator==(const Vector3 &v) { return x == v.x && y == v.y && z == v.z; }
};

Vector3 operator+(Vector3 a, Vector3 const &b) { return a += b; }

Vector3 operator-(Vector3 a, Vector3 const &b) { return a -= b; }

Vector3 Rotate90Z(const Vector3 &v) { return Vector3(-v.y, v.x, v.z); }

Vector3 Rotate90X(const Vector3 &v) { return Vector3(v.x, -v.z, v.y); }

Vector3 Rotate90Y(const Vector3 &v) { return Vector3(-v.z, v.y, v.x); }

Vector3 Rotate(Vector3 v, int rotation) {
	rotation = rotation % 24;
	if (rotation % 12 / 4 == 0) {
		if (rotation % 24 / 12 == 1)
			v = Rotate90X(Rotate90X(v));
	}
	if (rotation % 12 / 4 == 1) {
		if (rotation % 24 / 12 == 1)
			v = Rotate90Z(Rotate90Z(v));
		v = Rotate90Z(v);
	}
	if (rotation % 12 / 4 == 2) {
		if (rotation % 24 / 12 == 1)
			v = Rotate90Y(Rotate90Y(v));
		v = Rotate90X(v);
	}
	for (int i = 0; i < rotation % 4; ++i)
		v = Rotate90Y(v);
	return v;
}

template<typename T>
int IndexOf(std::vector<T> v, T t) {
	for (int i = 0, n = v.size(); i < n; ++i)
		if (v[i] == t)
			return i;
	return -1;
}

int main() {
	std::ifstream data("input_19_1.txt");
	if (!data.is_open()) return -1;

	std::vector<std::vector<Vector3>> scannerProbes;
	std::vector<Vector3> mappedProbes;
	std::vector<bool> mappedScanners;
	std::string line;
	while (std::getline(data, line)) {
		if (line.empty()) continue;
		if (line[1] == '-') {
			scannerProbes.push_back(std::vector<Vector3>());
			mappedScanners.push_back(false);
		} else {
			for (int i = 0; i < line.length(); ++i)
				if (line[i] == ',') line[i] = ' ';
			std::stringstream ss(line);
			int x, y, z;
			ss >> x;
			ss >> y;
			ss >> z;
			scannerProbes[scannerProbes.size() - 1].push_back(Vector3(x, y, z));
		}
	}

	for (int i = 0, n = scannerProbes[0].size(); i < n; ++i)
		mappedProbes.push_back(scannerProbes[0][i]);
	mappedScanners[0] = true;

	bool finished = false;
	while (!finished) {
		for (int s = 0; s < scannerProbes.size(); ++s) {
			if (mappedScanners[s]) continue;

			auto &scanner = scannerProbes[s];
			bool match = false;
			for (int rotation = 0; rotation < 24 && !match; ++rotation) {
				for (int i = 0; i < scanner.size() && !match; ++i) {
					for (int j = 0; j < mappedProbes.size() && !match; ++j) {
						std::vector<Vector3> matches;
						std::vector<Vector3> unmatches;
						Vector3 offset = mappedProbes[j] - Rotate(scanner[i], rotation);
						for (int p = 0; p < scanner.size(); ++p) {
							Vector3 probe = Rotate(scanner[p], rotation) + offset;
							if (IndexOf(mappedProbes, probe) != -1)
								matches.push_back(probe);
							else
								unmatches.push_back(probe);
						}

						if (matches.size() >= 12) {
							for (int k = 0; k < unmatches.size(); ++k)
								mappedProbes.push_back(unmatches[k]);
							match = true;
							mappedScanners[s] = true;
							std::cout << "Match " << s << " " << offset.x << "," << offset.y << "," << offset.z << std::endl;
						}
					}
				}
			}
		}
		std::cout << "Loop completed" << std::endl;

		finished = true;
		for (int i = 0; i < mappedScanners.size() && finished; ++i)
			finished &= mappedScanners[i];
	}

	std::cout << mappedProbes.size() << std::endl;

	return 0;
}
