#include "Ninja.hpp"


Ninja::Ninja(const string& name, Point& possition, int hits, int speed) : Character(name, possition, hits), speed(speed) {}

void Ninja::move(Character *enemy){
    Point p  = getLocation().moveTowards(this->getLocation(), enemy->getLocation(), speed);
    setLocation(p);
}



void Ninja::slash(Character *enemy){
    if(enemy == this) {
        throw std::runtime_error("Can't slash self.");
    }

    if(!enemy->isAlive()) {
        throw std::runtime_error("Enemy is already dead.");
    }

    if(!isAlive()) {
        throw std::runtime_error("Dead ninja can't slash");
    }

    if(isAlive() && this->getLocation().distance(enemy->getLocation()) <= 1 && enemy != nullptr && this != enemy){
        enemy->hit(LIVE_HIT_NINJA);
    }
}



string Ninja::print() {
     if(isAlive()){
        return "(N) Name: " + this->getName() + ",  LocationPoint: " + getLocation().print() + ", NumHits: " + to_string(this->getHitPoints());
    }
    return "(N) Name: (" + this->getName() + "),  LocationPoint: " + getLocation().print();
}