#include <iostream>
#include <fstream>

int main() {
    std::ifstream data("input_01_1.txt");
    if (!data.is_open()) return -1;

    int prevN, newN, count = 0;
    data >> prevN;
    while(data >> newN)
    {
        count += newN > prevN ? 1 : 0;
        prevN = newN;
    }
    std::cout << count;

    return 0;
}
