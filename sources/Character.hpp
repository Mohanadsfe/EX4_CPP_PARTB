#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <iostream>
#include <string>
#include "Point.hpp"
using namespace std;

class Character{


     Point location_point;
     int Number_hits;
     string name;
     bool in; // in or out team

    public:
       
        Character();
        Character(string, Point, int);
        virtual ~Character(); 
        Character(const Character& character);
        Character(Character* character);
        Character(Character&& character) noexcept; 

        Character& operator=(const Character&);
        Character& operator=(Character&&) noexcept;
       
        virtual bool isAlive(); 
        virtual double distance(Character*);
        virtual void hit(int damage); 
        virtual string print() = 0;
        
       
        string getName();
        Point& getLocation();
        int getHitPoints();
        bool getIsIN_Team();
        void setIsIN_Team(bool);
        void setLocation(Point point);
};
#endif