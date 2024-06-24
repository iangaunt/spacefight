#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

class Particle {
    public:
        static vector<Particle> particles;

        float brightness;
        int x, y;

        Particle(int x, int y);
        Particle(int x, int y, float brightness);

        void decrease_brightness();
        void calculate_spread(vector<vector<string>>& board);
        void add_to_board(vector<vector<string>>& board);
        static void update(vector<vector<string>>& board);
};

#endif