#include <iostream>
#include <fstream>

int min(int a, int b) { return a < b ? a : b ; }
int max(int a, int b) { return a > b ? a : b ; }

int main() {
    std::ifstream data("input_01_2.txt");
    if (!data.is_open()) return -1;

    int n, prevN = -1, newN, count = 0;
    int w[3] = {0,0,0};
    for (int i = 0; data >> n; ++i)
    {
        for (int j = 0; j <= min(i, 2); ++j)
            w[j] += n;

        if (i >= 2) {
            newN = w[(i-2)%3];
            count += prevN != -1 && newN > prevN ? 1 : 0;
            prevN = newN;
            w[(i-2)%3] = 0;
        }
    }
    std::cout << std::endl << count;

    return 0;
}
