#include "Board.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

Board::Board(int lengthh) {
    length = lengthh;
    generate_board();
}

Board::Board(int lengthh, vector<vector<string>> boardh) {
    length = lengthh;
    board = boardh;
}

void Board::print_board() {
    for (int i = 0; i < board.size(); i++) {
        string line = "";
        for (int j = 0; j < board[i].size(); j++) {
            line += board[i][j] + ' ';
        }
        cout << line << endl;
    }
    
    cout << endl;
}

void Board::generate_board() {
    vector<vector<string>> lines;
    const string dot = ".";

    for (int i = 0; i < length; i++) {
        vector<string> c;
        for (int j = 0; j < length; j++) {
            c.push_back(dot);
        }
        lines.push_back(c);
    }

    board = lines;
}

void Board::set_at(int x, int y, string icon) {
    board[x][y] = icon;
}

vector<vector<string>>* Board::get_board() {
    return &board;
}