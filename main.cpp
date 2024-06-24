#include <windows.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "headers/board.h"
#include "headers/entity.h"
#include "headers/particle.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main() {
    srand((unsigned) time(NULL));

    // Initializes a new Board variable.
    int length = 21;
    Board* board = new Board(length);
    vector<vector<string>>* b = board->get_board();

    // Initializes a new Entity variable.
    Entity* player = new Entity(b->size() - 1, b->size() / 2, 0, 0, "A");
    player -> add_to_board(*b);

    // Integer values to store the amount of ticks and frames passed.
    int ticks = 0;
    int max_ticks = 100000000;

    int frames = 0;

    // Score variable.
    int score = 0;

    // Vectors of entity types to update each frame.
    vector<Entity> projectiles;
    vector<Entity> enemies;

    // Main game loop. Will eventually run forever.
    for (int k = 0; k < 10000; k++) {
        // Clears the console and outputs the current state of the board.
        std::system("cls");
        cout << "SCORE: " << score << endl;
        cout << endl;

        board -> print_board();

        /* Debug stats.
        cout << "PROJECTILES SIZE: " << projectiles.size() << endl;
        cout << "ENEMIES SIZE: " << enemies.size() << endl;
        cout << "PARTICLES SIZE : " << Particle::particles.size() << endl;
        
        */

        cout << endl;

        // The frame delay of max_ticks function calls.
        for (ticks = 0; ticks < max_ticks; ticks++) {}

        // Resets player velocity.
        player -> vx = 0;
        player -> vy = 0;

        // Checks if player movement keys are pressed at the end of each frame.
        if (GetKeyState('W') & 0x8000) { player->vx = -1; }
        if (GetKeyState('S') & 0x8000) { player->vx = 1; }

        if (GetKeyState('A') & 0x8000) { player->vy = -1; }
        if (GetKeyState('D') & 0x8000) { player->vy = 1; }

        // Moves the player character.
        player -> move(*b);

        // Fires a projectile if the player is not at the very top of the screen.
        if (GetKeyState(' ') & 0x8000) {
            if (player->x != 0) {
                Entity* projectile = new Entity(player->x - 1, player->y, -1, 0, "^");
                projectile->add_to_board(*b);
                projectiles.push_back(*projectile);
            }
        }

        // Checks every projectile to see if it should be moved up or be deleted (out of view).
        for (int i = 0; i < projectiles.size(); i++) {
            Entity* proj = &projectiles.at(i);
            if (proj->x == 0) {
                board->set_at(proj->x, proj->y, " ");
                projectiles.erase(projectiles.begin() + i); 
                i--;
            } else {
                proj->move(*b);
                if (proj->x > 0 && (*b)[proj->x-1][proj->y] == "M") {
                    projectiles.erase(projectiles.begin() + i);
                    
                    score += 100;
                    Particle* p = new Particle(proj->x, proj->y, 0.99f);
                    Particle::particles.push_back(*p);
                    p->add_to_board(*b);

                    i--;
                }
            }
        }

        // Performs a random number check to see if an enemy is generated.
        bool enemySpawn = rand() % 3;
        if (enemySpawn == 0) {
            Entity* enemy = new Entity(0, rand() % length, 1, 0, "M");
            enemy->add_to_board(*b);
            enemies.push_back(*enemy);
        }

        // Checks every enemy to see if it should be moved down or be deleted (out of view).
        for (int i = 0; i < enemies.size(); i++) {
            Entity* enemy = &enemies.at(i);
            if (enemy->x == b->size() - 1) {
                board->set_at(enemy->x, enemy->y, " ");
                enemies.erase(enemies.begin() + i);
                i--;
            } else {
                enemy->move(*b);
                if (enemy->x < length - 1 && (*b)[enemy->x+1][enemy->y] == "^") {
                    board->set_at(enemy->x, enemy->y, " ");
                    enemies.erase(enemies.begin() + i);
                    i--;
                }
            }
        }
        
        // Updates the particles on screen.
        Particle::update(*b);
        frames++;
    }

    return 0;
}