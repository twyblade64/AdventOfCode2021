#include <iostream>
#include <fstream>

int main() {
    std::ifstream data("input.txt");
    if (!data.is_open()) return -1;

    int count[12] {0,0,0,0,0,0,0,0,0,0,0,0};
    std::string input;
    while (data >> input)
    {
        for (int i = 0; i < 12; ++i)
            count[i] += (input[i] == '0') ? -1 : 1;
    }
    int n = 0;
    for (int i = 0; i < 12; ++i)
        n = (n<<1) + (count[i] >= 0 ? 1 : 0);
    std::cout << (n*((~n)&0xFFF));

    return 0;
}
