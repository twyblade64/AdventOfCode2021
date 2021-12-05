// Solution where we only need to compare n[i] > n[i-4], inspired by afk-mario's solution
#include <iostream>
#include <fstream>

int main() {
    std::ifstream data("input_01_2_B.txt");
    if (!data.is_open()) return -1;

    int n, count = 0;
    int w[4] = {0,0,0,0};
    for (int i = 0; data >> n; ++i)
    {
        w[i%4] = n;
        if (i >= 3)
            count += w[i % 4] > w[(i+1) % 4] ? 1 : 0;
    }
    std::cout << std::endl << count;

    return 0;
}
