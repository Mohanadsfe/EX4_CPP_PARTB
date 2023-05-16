#include <string>
#include <stdexcept>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

#include "Team2.hpp"

namespace ariel{


    Team2::Team2(Character* leader) : Team(leader) {}


    void Team2::add(Character* other_team){
        if(this->team.size() >= 10){
            throw std::runtime_error("Max characters in team excided.");
        }
        if(other_team->getIsIN_Team()){
            throw std::runtime_error(other_team->getName() + " is already in a team.");
        }
        
        this->team.push_back(other_team);
        other_team->setIsIN_Team(true);
    }

    int Team2::stillAlive(){
        int counter = 0;
        for(size_t i = 0; i < team.size(); i++){
            if(team.at(i)->isAlive()) {
                counter++;
            }
        }
        return counter;
    }

     void Team2::attack(Team* enemy){
        if(enemy == nullptr) {
            throw invalid_argument("Can't attack nullptr.");
        }
        
        if(enemy == this) {
            throw invalid_argument("Can't attack self.");
        }

        if(enemy->stillAlive() <= 0 || this->stillAlive() <= 0) {
            return;
        }

        if (!this->getLeader()->isAlive()) {
            chooseNew_Leader();
        }

        Character* closer_enemy = getCloserEnemy(enemy);

        for(size_t i = 0; i < getTeam().size(); i++) {
            if(enemy->stillAlive() <= 0 || this->stillAlive() <= 0) {
                break;
            }

            if(!closer_enemy->isAlive()) {
                closer_enemy = getCloserEnemy(enemy);
            }

            Cowboy* cowboy = dynamic_cast<Cowboy*>(getTeam().at(i));

            if(cowboy != nullptr && cowboy->isAlive()) {
                if(cowboy->hasboolets()) {
                    cowboy->shoot(closer_enemy);
                }
                else {
                    cowboy->reload();
                }
            }
            else {
                Ninja* ninja = dynamic_cast<Ninja*>(getTeam().at(i));
            
                if(ninja != nullptr && ninja->isAlive()) {
                    if(ninja->distance(closer_enemy) < 1) {
                        ninja->slash(closer_enemy);
                    }
                    else {
                        ninja->move(closer_enemy);
                    }
                }
            }
        }
    }

    void Team2::print(){
     
       
        for (size_t i = 0; i <this->team.size(); i++)
        {

          if(team[i]!=nullptr){

           cout << team[i]->print();   
           cout << endl;

            }
        }
    }

    std::vector<Character*> Team2::getTeam() const {
        return this->team;
    }

    Character* Team2::getLeader() const {
        return this->leader;
    }
}
