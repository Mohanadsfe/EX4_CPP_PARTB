#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Character.hpp"


Character::Character()  // defualt constructor
: name(""), location_point(Point()), Number_hits(0), in(false) {}


/////////////////////////////////////////////////////  Rconstructor

Character::Character(string name, Point possition, int Number_hits) 
: name(name), location_point(possition), Number_hits(Number_hits), in(false) {}


///////////////////////////////////////////////////// empty constructor

Character::~Character() {


}


///////////////////////////////////////////////////// copy constructor

Character::Character(const Character& character) 
: Character(character.name, character.location_point, character.Number_hits) {}


///////////////////////////////////////////////////// copy constructor

Character::Character(Character* character)
 : Character(character->name, character->location_point, character->Number_hits){}


///////////////////////////////////////////////////// move constructor

Character::Character(Character&& character) noexcept 
: name(character.name), location_point(character.location_point), Number_hits(character.Number_hits), in(character.in){}

/////////////////////////////////////////////////////




Character& Character::operator=(const Character& character){
    this->name = character.name;
    this->location_point = character.location_point;
    this->Number_hits = character.Number_hits;
    this->in = character.in;
    return *this;
}

Character& Character::operator=(Character&& character) noexcept{
    this->name = character.name;
    this->location_point = character.location_point;
    this->Number_hits = character.Number_hits;
    this->in = character.in;
    return *this;
}


bool Character::isAlive(){
    return this->Number_hits > 0;
}

double Character::distance(Character* character){
    return location_point.distance(character->location_point);
}

void Character::hit(int damage){
    if(damage < 0){
        throw std::invalid_argument("Can't hit negative points.");
    }
    this->Number_hits -= damage;
}


/////////////////////////////////////////

string Character::getName(){
    return this->name;
}

Point& Character::getLocation(){
    return location_point;
}


void Character::setLocation(Point point){

    this->location_point.setX(point.getX());
    this->location_point.setY(point.getY());

}



int Character::getHitPoints(){
    return Number_hits;
}

bool Character::getIsIN_Team() {
    return in;
}

void Character::setIsIN_Team(bool newSet) {
    this->in = newSet;
}