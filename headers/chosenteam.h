#ifndef CHOSENTEAM_H
#define CHOSENTEAM_H

#include "fightclub.h"

class ChosenTeam: public SubState {
    private:
        Team* team;
        TwoVsTwo* parentState;

    public:
        ChosenTeam(Screen* screen, TwoVsTwo* parentState, Team* team, float start = 0.0f);
        ~ChosenTeam();
        void keyInput(int key);
        void update(int deltaTime);
};

#endif // CHOSENTEAM_H
