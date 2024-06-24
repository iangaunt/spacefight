#include "../headers/entity.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * @brief Checks to see if the ordered pair (x, y) exists on the board.
 * 
 * @param x The x coordinate to check.
 * @param y The y coordinate to check.
 * @param board The board to compare the x and y coordinates to for validity.
 * 
 * @return true if the coordinate exists somewhere in the board,
 * @return false if not (invalid position)
 */
bool is_valid_position(int x, int y, vector<vector<string>>& board) {
    return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
}

/**
 * @brief Swaps the positions of two characters on the board. This can be
 * used for checking collisions of two entities or for moving the player character around.
 * 
 * @param x1 The first x coordinate to swap.
 * @param y1 The first y coordinate to swap.
 * @param x2 The second x coordinate to swap.
 * @param y2 The second y coordinate to swap.
 * @param board The board to swap entities on.
 */
void swap_positions(int x1, int y1, int x2, int y2, vector<vector<string>>& board) {
    string temp = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = temp;
}

/**
 * @brief Construct a new Entity object.
 * 
 * @param xh The x coordinate of the new entity.
 * @param yh The y coordinate of the new entity.
 * @param vxh The initial x velocity.
 * @param vyh The initial y velocity.
 * @param iconh The icon to display the entity with when placed on a Board.
 */
Entity::Entity(int xh, int yh, int vxh, int vyh, string iconh) {
    x = xh;
    y = yh;
    vx = vxh;
    vy = vyh;
    icon = iconh;
}

/**
 * @brief Attempts to move an entity on a board based on their velocity
 * and blocks their movement if the next tile they would traverse to is
 * out of bounds.
 * 
 * @param board The board to move the entity on.
 */
void Entity::move(vector<vector<string>>& board) {
    if (is_valid_position(x + vx, y + vy, board)) {
        board[x][y] = " ";
        board[x + vx][y + vy] = icon;

        x += vx;
        y += vy;
    }
}

/**
 * @brief Places the entity on a new (x, y) position. 
 * This is NOT a fully safe call and the `move()` method should
 * be used instead if the position may be out of bounds.
 * 
 * @param xh The new x coordinate.
 * @param yh The new y coordinate.
 */
void Entity::move_to(int xh, int yh) {
    x = xh;
    y = yh;
}

/**
 * @brief Places the entity on the specified board based on 
 * its initial positioning values.
 * 
 * @param board The board to put the entity on.
 */
void Entity::add_to_board(vector<vector<string>>& board) { board[x][y] = icon; }