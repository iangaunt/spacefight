#ifndef BOARD_H_
#define BOARD_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

class Board {
    public:
        int length;

        Board(int length);
        Board(int length, vector<vector<string>> board);

        void print_board();
        void generate_board();
        void set_at(int x, int y, string icon);
        
        vector<vector<string>>* get_board();

    private:
        vector<vector<string>> board;
};

#endif