#include <iostream>
#include <fstream>

int main() {
    std::ifstream data("input_02_2.txt");
    if (!data.is_open()) return -1;

    std::string cmd;
    int x = 0, y = 0, aim = 0, dist;
    while (data >> cmd)
    {
        data >> dist;
        switch(cmd[0])
        {
            case 'f': x += dist; y += aim * dist; break;
            case 'd': aim -= dist; break;
            case 'u': aim += dist; break;
        }
    }
    std::cout << x*(-y);

    return 0;
}
