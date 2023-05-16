#ifndef NINJA_HPP
#define NINJA_HPP
#include <string>
#include "Character.hpp"
using namespace std;
constexpr int LIVE_HIT_NINJA = 40;


class Ninja : public Character {
    public:
        
        Ninja(const string&, Point&, int, int);
        virtual void move(Character *enemy);
        virtual void slash(Character *enemy);
        string print() override;

        int speed;
};
#endif