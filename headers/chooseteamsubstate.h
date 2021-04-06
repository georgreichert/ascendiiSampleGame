#ifndef CHOOSETEAMSUBSTATE_H
#define CHOOSETEAMSUBSTATE_H

#include "fightclub.h"

class ChooseTeamSubState: public SubState {
    private:
        std::vector<MenuElement*> menuElements;
        std::vector<Team*> teams;
        int cursorPosition = 0;
        TwoVsTwo* parentState;
        bool playerType;

    public:
        ChooseTeamSubState(Screen* screen, TwoVsTwo* parentState, bool playerType, float start = 0.0f);
        ~ChooseTeamSubState();
        void keyInput(int key);
        void update(int deltaTime);
};

#endif // CHOOSETEAMSUBSTATE_H
