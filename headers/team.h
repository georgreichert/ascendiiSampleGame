#ifndef TEAM_H
#define TEAM_H

#include "fightclub.h"

class Team {
    private:
        Fighter* fighters[2];
        std::string name;
        bool playerType = false;
        int victories = 0;
        int defeats = 0;

    public:
        Team(Fighter* fighter1, Fighter* fighter2, std::string name);
        Fighter* getFighter(int index);
        std::string getName();
        void setPlayerType(bool type);
        bool getPlayerType();
        int getVictories();
        int getDefeats();
        void victory();
        void defeat();
};

#endif // TEAM_H
