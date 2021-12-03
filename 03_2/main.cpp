#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream data("input.txt");
    if (!data.is_open()) return -1;

    int SIZE = 12;
    std::string input;
    std::vector<int> values;
    while (data >> input) {
        int n = 0;
        for (int i = 0; i < SIZE; ++i)
            n = (n << 1) + (input[i] == '1' ? 1 : 0);
        values.push_back(n);
    }

    int mostCommon = 0;
    int leastCommon = 0;
    for (int i = 0; i < SIZE; ++i) {
        int mostCommonCount = 0;
        int leastCommonCount = 0;
        int leastN = 0;
        int bit = (1 << (SIZE - 1 - i));
        for (int j = 0; j < values.size(); ++j) {
            if ((values[j] >> (SIZE - i)) == mostCommon)
                mostCommonCount += ((values[j] & bit) > 0) ? 1 : -1;
            if ((values[j] >> (SIZE - i)) == leastCommon)
            {
                leastCommonCount += ((values[j] & bit) > 0) ? 1 : -1;
                ++leastN;
            }
        }
        mostCommon = (mostCommon << 1) + (mostCommonCount >= 0 ? 1 : 0);
        leastCommon = (leastCommon << 1) + (((leastCommonCount >= 0) == (leastN > 1)) ? 0 : 1);
    }
    std::cout << (mostCommon * leastCommon);
    return 0;
}