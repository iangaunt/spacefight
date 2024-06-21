#include "Entity.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

bool is_valid_position(int x, int y, vector<vector<string>>& board) {
    return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
}

void swap_positions(int x1, int y1, int x2, int y2, vector<vector<string>>& board) {
    string temp = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = temp;
}

Entity::Entity(int xh, int yh, int vxh, int vyh, string iconh) {
    x = xh;
    y = yh;
    vx = vxh;
    vy = vyh;
    icon = iconh;
}

void Entity::move(vector<vector<string>>& board) {
    if (is_valid_position(x + vx, y + vy, board)) {
        move_to(x + vx, y + vy);

        x += vx;
        y += vy;
    }
}

void Entity::move_to(int xh, int yh) {
    x = xh;
    y = yh;
}

void Entity::add_to_board(vector<vector<string>>& board) {
    board[x][y] = icon;
}