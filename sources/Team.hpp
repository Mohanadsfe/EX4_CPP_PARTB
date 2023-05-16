#ifndef TEAM_HPP
#define TEAM_HPP
#include <vector>
#include <type_traits>
#include "Point.hpp"
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"
#include<limits>
using namespace std;
constexpr int SIZE = 10;


namespace ariel{
    class Team {
        public:
            Character* leader;
            std::vector<Character*> team;

            Team(Character* leader);
            virtual ~Team(); 
            Team(const Team& other_team); 
            Team(Team&& other_team) noexcept; 

            Team& operator=(const Team&);
            Team& operator=(Team&&) noexcept;

            virtual void add(Character*);
            void attack(Team*);
            int stillAlive();
            void print();

            void chooseNew_Leader();
            Character* getCloserEnemy(Team* enemy);
            void sortTeam();

         
            std::vector<Character*> getTeam() const;
            Character* getLeader() const;


            template<typename Base, typename T>
            inline bool instanceof(const T *ptr) {
            return dynamic_cast<const Base*>(ptr) != nullptr;
            }

    };
};
#endif