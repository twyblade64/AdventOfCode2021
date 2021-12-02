#include <iostream>
#include <fstream>

int main() {
    std::ifstream data("input.txt");
    if (!data.is_open()) return -1;

    std::string cmd;
    int x = 0, y = 0, dist;
    while (data >> cmd)
    {
        data >> dist;
        switch(cmd[0])
        {
            case 'f': x += dist; break;
            case 'd': y -= dist; break;
            case 'u': y += dist; break;
        }
    }
    std::cout << x*(-y);

    return 0;
}
