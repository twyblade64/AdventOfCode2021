#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#define BOARD_SIZE 5

struct BoardSlot {
    int number;
    bool marked;
};

int main() {
    std::ifstream data("input_04_2.txt");
    if (!data.is_open()) return -1;

    std::string input;
    data >> input;

    std::stringstream ss(input);
    std::vector<int> numbers;
    int n;
    while (ss >> n) {
        numbers.push_back(n);
        if (ss.peek() == ',')
            ss.ignore();
    }

    std::vector<BoardSlot**> boards;
    std::vector<bool> boardsBingo;

    for (int i = 0; data.ignore(); ++i){
        BoardSlot** board = new BoardSlot*[BOARD_SIZE];
        for (int x = 0; x < BOARD_SIZE; ++x) {
            board[x] = new BoardSlot[BOARD_SIZE];
            for (int y = 0; y < BOARD_SIZE; ++y) {
                data >> n;
                board[x][y].number = n;
                board[x][y].marked = false;
            }
        }
        boards.push_back(board);
        boardsBingo.push_back(false);
    }

    int bingoCount = boardsBingo.size();
    int bingoBoard = -1;
    int bingoNumber = -1;
    for (int i = 0; i < numbers.size() && bingoBoard == -1; ++i) {
        n = numbers[i];
        for (int b = 0; b < boards.size() && bingoBoard == -1; ++b) {
            if (boardsBingo[b]) continue;

            int x, y;
            bool marked = false;
            for (y = 0; y < BOARD_SIZE && !marked; ++y) {
                for (x = 0; x < BOARD_SIZE && !marked; ++x) {
                    if (boards[b][x][y].number == n) {
                        boards[b][x][y].marked = true;
                        marked = true;
                    }
                }
            }
            if (marked)
            {
                --x;--y;
                bool xBingo = true;
                bool yBingo = true;
                for (int j = 0; j < BOARD_SIZE; ++j)
                {
                    xBingo &= boards[b][x][j].marked;
                    yBingo &= boards[b][j][y].marked;
                }

                if (xBingo || yBingo)
                {
                    --bingoCount;
                    boardsBingo[b] = true;
                    if (bingoCount == 0) {
                        bingoBoard = b;
                        bingoNumber = n;
                    }
                }
            }
        }
    }

    n = 0;
    for (int y = 0; y < BOARD_SIZE; ++y)
        for (int x = 0; x < BOARD_SIZE; ++x)
            if (!boards[bingoBoard][x][y].marked)
                n += boards[bingoBoard][x][y].number;

    std::cout << bingoNumber * n;
    return 0;
}
