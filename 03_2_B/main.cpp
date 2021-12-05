#include <iostream>
#include <fstream>
#include <cstring>

int main() {
    std::ifstream data("input_03_2.txt");
    if (!data.is_open()) return -1;

    int count[0xFFFFu];
    memset(count, 0, sizeof(count));

    int SIZE = 12;
    std::string input;
    while (data >> input) {
        int n = 0;
        for (int i = 0; i < SIZE; ++i) {
            n += (input[i] == '1' ? 1 : 0) << (SIZE - 1 - i);
            ++count[(i<<SIZE)+n];
        }
    }

    int mostCommon = 0;
    int leastCommon = 0;
    for (int i = 0; i < SIZE; ++i) {
        int bit = (1 << (SIZE - 1 - i));
        int mostCommonCount = count[(i<<SIZE)+mostCommon+bit] - count[(i<<SIZE)+mostCommon];
        int leastCommonCount = count[(i<<SIZE)+leastCommon+bit] - count[(i<<SIZE)+leastCommon];
        bool singleValue = count[(i<<SIZE)+leastCommon+bit] == 0 || count[(i<<SIZE)+leastCommon] == 0;

        mostCommon += (mostCommonCount >= 0 ? 1 : 0) << (SIZE - 1 - i);
        leastCommon += (((leastCommonCount >= 0) != singleValue) ? 0 : 1) << (SIZE - 1 - i);
    }
    std::cout << (mostCommon * leastCommon);
    return 0;
}