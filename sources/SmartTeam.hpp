#ifndef SMARTTEAM_HPP
#define SMARTTEAM_HPP
#include "Team.hpp"

namespace ariel{
    class SmartTeam : public ariel::Team {
        public:
            SmartTeam(Character* leader);
            void add(Character* other_team) override;
            void attack(Team*);

            void chooseNew_Leader(Team* enemy);
            Character* getCloserEnemy(Team* enemy);
    };
};
#endif