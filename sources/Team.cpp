#include <string>
#include <stdexcept>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Team.hpp"

namespace ariel {


    Team::Team(Character* leader) {

        if(leader->getIsIN_Team()){
            throw std::runtime_error(leader->getName() + " is already in a team.");
        }

        this->leader = leader;
        team.push_back(leader);
        leader->setIsIN_Team(true);
    }

    Team::~Team(){

        for(std::vector<Character*>::iterator iter=team.begin(); iter != team.end(); iter++) {
            delete *iter;
        }

    } 

    Team::Team(const Team& other_team) : Team(other_team.leader) {
        for(size_t i = 0; i < other_team.team.size(); i++) {
            this->team.push_back(other_team.team[i]);
        }
    }

    Team::Team(Team&& other_team) noexcept : Team(other_team.leader) {
        for(size_t i = 0; i < other_team.team.size(); i++) {
            this->team.push_back(other_team.team[i]);
        }
        other_team.leader = nullptr;
        other_team.team.clear();
    }

    Team& Team::operator=(const Team& other_team){
        this->leader = other_team.leader;
        this->team = other_team.team;
        return *this;
    }

    Team& Team::operator=(Team&& other_team) noexcept{
        this->leader = other_team.leader;
        this->team = other_team.team;
        return *this;
    }

    void Team::add(Character* character){
        if(team.size() >= SIZE){
            throw std::runtime_error("Max characters in team excided.");
        }
        if(character->getIsIN_Team()){
            throw std::runtime_error(character->getName() + " is already in a team.");
        }
        
        team.push_back(character);
        character->setIsIN_Team(true);
    }

   void Team::attack(Team* enemy){
        if(enemy == nullptr) {
            throw invalid_argument("Can't attack nullptr.");
        }
        
        if(enemy == this) {
            throw invalid_argument("Can't attack self.");
        }

        if(enemy->stillAlive() <= 0) {
                throw runtime_error("Can't attack dead team.");
        }

        if (!this->leader->isAlive()) {
            chooseNew_Leader();
        }

        Character* closer_enemy = getCloserEnemy(enemy);

        for(size_t i = 0; i < this->team.size(); i++) {
            if(enemy->stillAlive() <= 0 || this->stillAlive() <= 0) {
                break;
            }

            if(!closer_enemy->isAlive()) {
                closer_enemy = getCloserEnemy(enemy);
            }

            Cowboy* cowboy = dynamic_cast<Cowboy*>(this->team.at(i));

            if(cowboy != nullptr && cowboy->isAlive()) {
                if(cowboy->hasboolets()) {
                    cowboy->shoot(closer_enemy);
                }
                else {
                    cowboy->reload();
                }
            }
        }

        for(size_t i = 0; i < this->team.size(); i++) {
            if(enemy->stillAlive() <= 0 || this->stillAlive() <= 0) {
                break;
            }

            if(!closer_enemy->isAlive()) {
                closer_enemy = getCloserEnemy(enemy);
            }

            Ninja* ninja = dynamic_cast<Ninja*>(this->team.at(i));
            
            if(ninja != nullptr && ninja->isAlive()) {
                if(ninja->distance(closer_enemy) <= 1) {
                    ninja->slash(closer_enemy);
                }
                else {
                    ninja->move(closer_enemy);
                }
            }
        }
    }

    int Team::stillAlive(){
        int counter = 0;
        for(size_t i = 0; i < team.size(); i++){
            if(team.at(i)->isAlive()) {
                counter++;
            }
        }
        return counter;
    }

     void Team::print(){

        this->sortTeam();

        for (size_t i = 0; i <this->team.size(); i++)
        {

          if(team[i]!=nullptr){

           cout << team[i]->print();   
           cout << endl;

            }
        }

    }

    void Team::chooseNew_Leader() {

        double distance = std::numeric_limits<double>::max();
        size_t index = (size_t)-1;
        
        for(size_t i = 0; i < team.size(); i++) {
            Character* any_Leader = team.at(i);
            if (any_Leader->isAlive() && any_Leader != this->leader && any_Leader->distance(this->leader) < distance) {
               distance = any_Leader->distance(this->leader);
               index = i;
            }
        }
        
        if (index != -1) {
            this->leader = team.at(index);
        }
    }

    Character* Team::getCloserEnemy(Team* enemy) {

        double distance = std::numeric_limits<double>::max();


        size_t index = (size_t)-1;
        
        for(size_t i = 0; i < enemy->team.size(); i++) {
            Character* any_closer_enemy = enemy->team.at(i);
            
            if (any_closer_enemy->isAlive() && any_closer_enemy != this->leader && any_closer_enemy->distance(this->leader) < distance) {
               distance = any_closer_enemy->distance(this->leader);
               index = i;
            }
        }
        
        return (index != -1) ? enemy->team.at(index) : nullptr;
    }

    void Team::sortTeam(){
        
        vector<Character*> cowboys = vector<Character*>();
        vector<Character*> ninjas = vector<Character*>();
 

        for(size_t i =0; i<this->team.size(); i++){

        if(team[i]!=nullptr){

            if(instanceof<Cowboy>(team[i])){

                cowboys.push_back(team[i]);

                }else{

                ninjas.push_back(team[i]);

            }

            }

        }
       


        this->team.clear();


        for(size_t i =0; i<ninjas.size(); i++){

            this->team.push_back(ninjas[i]);
      
         }

        for(size_t i =0; i<cowboys.size(); i++){

            this->team.push_back(cowboys[i]);
       
         }



    }

    std::vector<Character*> Team::getTeam() const {
        return this->team;
    }

    Character* Team::getLeader() const {
        return this->leader;
    }
}
