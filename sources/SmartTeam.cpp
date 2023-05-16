#include <string>
#include <stdexcept>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

#include "SmartTeam.hpp"

namespace ariel{
    SmartTeam::SmartTeam(Character* leader) : Team(leader) {}

    void SmartTeam::add(Character* other_team){
        if(this->team.size() >= SIZE){
            throw std::runtime_error("Max characters in team excided.");
        }
        if(other_team->getIsIN_Team()){
            throw std::runtime_error(other_team->getName() + " is already in a team.");
        }
        
        this->team.push_back(other_team);
        other_team->setIsIN_Team(true);
    }

    void SmartTeam::chooseNew_Leader(Team* enemy) {
        int maxScore = 0;
        Character* selectedCandidate = nullptr;
        double distance = std::numeric_limits<double>::max();
        
        for(size_t i = 0; i < team.size(); i++) {
            int score = 0;

            Character* leadCandidate = team.at(i);
            if(!leadCandidate->isAlive()) {
                continue;
            }

            for(size_t j = 0; j < team.size(); j++) {
                if(leadCandidate == team.at(j)) {
                    continue;
                }

                YoungNinja* yninja = dynamic_cast<YoungNinja*>(this->team.at(j));
                TrainedNinja* tninja = dynamic_cast<TrainedNinja*>(this->team.at(j));
                OldNinja* oninja = dynamic_cast<OldNinja*>(this->team.at(j));
                Cowboy* cowboy = dynamic_cast<Cowboy*>(this->team.at(j));
                if(yninja != nullptr && yninja->distance(leadCandidate) <= yninja->speed) {
                    score++;
                    continue;
                }
                else if(tninja != nullptr && tninja->distance(leadCandidate) <= tninja->speed) {
                    score++;
                    continue;
                }
                else if(oninja != nullptr && oninja->distance(leadCandidate) <= oninja->speed) {
                    score++;
                    continue;
                }
                else if(cowboy != nullptr) {
                    score++;
                    continue;
                }
            }
            
            for(size_t j = 0; j < enemy->getTeam().size(); j++){
                Character* enemyMember = enemy->getTeam().at(j);

                YoungNinja* yninja = dynamic_cast<YoungNinja*>(leadCandidate);
                TrainedNinja* tninja = dynamic_cast<TrainedNinja*>(leadCandidate);
                OldNinja* oninja = dynamic_cast<OldNinja*>(leadCandidate);
                Cowboy* cowboy = dynamic_cast<Cowboy*>(leadCandidate);
                if(yninja != nullptr && yninja->distance(enemyMember) <= yninja->speed) {
                    score++;
                    continue;
                }
                else if(tninja != nullptr && tninja->distance(enemyMember) <= tninja->speed) {
                    score++;
                    continue;
                }
                else if(oninja != nullptr && oninja->distance(enemyMember) <= oninja->speed) {
                    score++;
                    continue;
                }
                else if(cowboy != nullptr && cowboy->hasboolets()) {
                    score++;
                    continue;
                }
            }

            if(maxScore < score) {
                maxScore = score;
                selectedCandidate = leadCandidate;
            }
        }
        if(selectedCandidate != nullptr) {
            this->leader = selectedCandidate;
        }
    }

    Character* SmartTeam::getCloserEnemy(Team* enemy) {
        double distance = std::numeric_limits<double>::max();
        size_t index = (size_t)-1;
        
        for(size_t i = 0; i < enemy->team.size(); i++) {
            Character* any_enemy = enemy->team.at(i);
            
            if (any_enemy->isAlive() && any_enemy != this->leader && any_enemy->distance(this->leader) < distance) {
               distance = any_enemy->distance(this->leader);
               index = i;
            }
        }
        
        return (index != -1) ? enemy->team.at(index) : nullptr;
    }
}
