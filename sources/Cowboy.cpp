#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "Cowboy.hpp"


Cowboy::Cowboy(string name, Point point) : Character(name, point, 110) {
    bulletsStack = REALOD_SIZE;
}

// Cowboy::~Cowboy(){
//    // delete this;
// }

//////////////////////////////////////////////////


void Cowboy::shoot(Character *enemy){
    if(enemy == this) {
        throw std::runtime_error("Can't shoot self.");
    }
    
    if(!enemy->isAlive()) {
        throw std::runtime_error("Enemy is already dead.");
    }

    if(!isAlive()) {
        throw std::runtime_error("Dead cowboy can't shoot");
    }
   
    if(isAlive() && hasboolets() && enemy != nullptr && this != enemy){
        enemy->hit(LIVE_HIT);
        bulletsStack -= 1;
    }
}

bool Cowboy::hasboolets(){
    return bulletsStack > 0;
}

void Cowboy::reload(){
    if(!isAlive()) {
        throw std::runtime_error("Can't reload to dead cowboy.");
    }
    bulletsStack = REALOD_SIZE;
}

string Cowboy::print() {
    if(isAlive()){
        return "(C) Name: " + this->getName() + ", LocationPoint: " + this->getLocation().print() + ", NumHits: " + to_string(this->getHitPoints());
    }
    return "(C) Name: (" + this->getName() + "), LocationPoint: " + this->getLocation().print();
}