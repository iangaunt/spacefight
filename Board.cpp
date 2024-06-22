#include "base/board.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/**
 * @brief Construct a new Board object with a given length and generates it.
 * 
 * @param lengthh The length of the new board to generate.
 */
Board::Board(int lengthh) {
    length = lengthh;
    generate_board();
}

/**
 * @brief Construct a new Board object with a pre-generated board.
 * 
 * @param lengthh The length of the board to generate.
 * @param boardh The board to be used instead of a clean generation.
 */
Board::Board(int lengthh, vector<vector<string>> boardh) {
    length = lengthh;
    board = boardh;
}

/**
 * @brief Outputs the board variable line by line with spaced out characters.
 */
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

/**
 * @brief Generates a new board based on the specified length variable.
 * Boards are `length` by `length` in size.
 */
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

/**
 * @brief Adds a specified character at the passed in x and y coordinate.
 * 
 * @param x The x coordinate to put the icon at.
 * @param y The y coordinate to put the icon at.
 * @param icon The single-character string to place at (x, y).
 */
void Board::set_at(int x, int y, string icon) {
    board[x][y] = icon;
}

/**
 * @brief Returns the board as a vector of string vectors, where 
 * every character on the board is stored individually.
 * 
 * @return `vector<vector<string>>*` (The address in memory of the first vector dimension)
 */
vector<vector<string>>* Board::get_board() {
    return &board;
}