#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

class Entity {
    public: 
        int x, y;
        int vx, vy;
        string icon = " ";

        Entity(int xh, int yh, int vxh, int vyhm, string icon);
        
        void move(vector<vector<string>>& board);
        void move_to(int x, int y);

        void add_to_board(vector<vector<string>>& board);
};

#endif