#include <windows.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "base/board.h"
#include "base/entity.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main() {
    // Initializes a new Board variable.
    int length = 21;
    Board* board = new Board(length);
    vector<vector<string>>* b = board->get_board();

    // Initializes a new Entity variable.
    Entity* player = new Entity(b->size() - 1, b->size() / 2, 0, 0, "A");
    player -> add_to_board(*b);

    // Integer values to store the amount of ticks and frames passed.
    int ticks = 0;
    int max_ticks = 200000000;

    int frames = 0;

    // A vector of projectile entities to take care of.
    vector<Entity> projectiles;

    // Main game loop. Will eventually run forever.
    for (int k = 0; k < 10000; k++) {
        // Clears the console and outputs the current state of the board.
        std::system("cls");
        board -> print_board();

        // The frame delay of max_ticks function calls.
        for (ticks = 0; ticks < max_ticks; ticks++) {}
        player -> icon = "A";
        player -> vx = 0;
        player -> vy = 0;

        // 
        if (GetKeyState('W') & 0x8000) { player -> vx = -1; }
        if (GetKeyState('S') & 0x8000) { player -> vx = 1; }

        if (GetKeyState('A') & 0x8000) { player -> vy = -1; }
        if (GetKeyState('D') & 0x8000) { player -> vy = 1; }

        if (GetKeyState(' ') & 0x8000) { 
            Entity* p = new Entity(player -> x - 1, player -> y, player -> vx, player -> vy, "^");
            p -> vx = -1;

            p -> add_to_board(*b);
            projectiles.push_back(*p);
        }

        for (int i = 0; i < projectiles.size(); i++) {
            Entity proj = projectiles.at(i);
            if (proj.icon == "^") {
                proj.move(*b);
                projectiles.erase(projectiles.begin() + i);
                i--;
            }
        }
        
        player -> move(*b);
        frames++;
    }

    return 0;
}