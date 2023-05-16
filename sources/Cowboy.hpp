#ifndef COWBOY_HPP
#define COWBOY_HPP
#include <string>
#include "Character.hpp"
using namespace std;
constexpr int REALOD_SIZE = 6;
constexpr int LIVE_HIT = 10;

class Cowboy : public Character {

   
    int bulletsStack;

    public:
      
        Cowboy(string, Point);
        //~Cowboy();
        void shoot(Character *enemy); 
        bool hasboolets();
        void reload(); 
        string print() override;

};
#endif
