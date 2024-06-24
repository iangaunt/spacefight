#include "../headers/particle.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using std::find;
using std::string;
using std::vector;

// The gradient of characters representing the brightness of a particle.
string gradient = ".',:;Il!i><~+_-?][}{1)(|/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#W&8%B@";

// The empty string for concatenation purposes.
const string empty = "";

// The static vector of particles that are updated in the main game loop.
vector<Particle> Particle::particles;

// The positions on screen where new particles cannot be placed (used for optimization).
vector<string> locked_positions;

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
bool is_valid(int x, int y, vector<vector<string>>& board) {
    return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
}

/**
 * @brief Checks to see if a position string code is contained in the 
 * `locked_positions` vector so particles cannot be double-placed,
 * reducing calculation load.
 * 
 * @param pos The position string in the form of `"x.y"`.
 * 
 * @return true if the coordinate has been locked by another particle,
 * @return false if the coordinate is free.
 */
bool position_is_locked(string pos) {
    for (int i = 0; i < locked_positions.size(); i++) {
        if (pos == locked_positions[i]) return true;
    }
    return false;
}

/**
 * @brief Creates a new particle without an initial brightness value.
 * 
 * @param xh The x coordinate of the particle.
 * @param yh The y coordinate of the particle.
 */
Particle::Particle(int xh, int yh) {
    x = xh;
    y = yh;
}

/**
 * @brief Creates a new particle with an initial brightness value.
 * 
 * @param xh The x coordinate of the particle.
 * @param yh The y coordinate of the particle.
 * @param brightnessh The brightness of the particle.
 */
Particle::Particle(int xh, int yh, float brightnessh) {
    x = xh;
    y = yh;
    brightness = brightnessh;
}

/**
 * @brief Decreases the brightness of the particle by a random amount,
 * which will change what character is displayed on the board at its coordinates.
 */
void Particle::decrease_brightness() {
    brightness -= (rand() % 10 + 1) * 0.03;
    brightness -= (rand() % 1000) / 10000;
}

/**
 * @brief Checks the eight tiles around a particle and randomly selects if 
 * a new darker satellite particle is created. This creates the effect of an 
 * explosion moving outward where less heat is generated farther from the point
 * of impact.
 * 
 * @param board The board to update.
 */
void Particle::calculate_spread(vector<vector<string>>& board) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            if (!is_valid(x + i, y + j, board)) continue;

            if (board[x + i][y + j] == " ") {
                string pos = (x + i) + "." + (y + j);

                if (rand() % 2 == 0 && !position_is_locked(pos)) {
                    Particle* p = new Particle(x + i, y + j, brightness);
                    locked_positions.push_back(pos);
                    particles.push_back(*p);
                }
            }
        }
    }
}

/**
 * @brief Places a particle on the board at a specific index with a 
 * specific character depending on its brightness.
 * 
 * @param board The board to place the particle on.
 */
void Particle::add_to_board(vector<vector<string>>& board) {
    int index = floor((float) (gradient.size()) * brightness);
    if (index < 0 || index > gradient.size() - 1) return;

    char icon = gradient[index];

    if (is_valid(x, y, board)) {
        if (board[x][y] != "A") {
            board[x][y] = icon + empty;
        }
    }
}

/**
 * @brief Iterates through the stored particles array and decreases
 * its relative brightness, checks for satellite particle generation,
 * and updates its icon on the board. If ther particle is too dark,
 * then it is removed.
 * 
 * @param board The board to update.
 */
void Particle::update(vector<vector<string>>& board) {
    std::cout << particles.size() << std::endl;
    locked_positions.clear();

    for (int i = 0; i < particles.size(); i++) {
        Particle* part = &particles[i];

        if (part->brightness > 0.0) {
            part->decrease_brightness();
            part->calculate_spread(board);

            part->add_to_board(board);
        } else {
            if (board[part->x][part->y] != "A") board[part->x][part->y] = " ";
            particles.erase(particles.begin() + i);
            i--;
        }
    }
}