#ifndef NEWTEAM_H
#define NEWTEAM_H

#include "fightclub.h"

class NewTeam: public SubState {
    private:
        std::vector<Fighter*> fighters;
        GameState* parentState;
        NewTeamMenu* menu;

    public:
        NewTeam(Screen* screen, GameState* parentState, float start = 0.0f);
        ~NewTeam();
        void keyInput(int key);
        void update(int deltaTime);
};

#endif // NEWTEAM_H
