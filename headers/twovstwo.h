#ifndef TWOVSTWO_H
#define TWOVSTWO_H

#include "fightclub.h"

class TwoVsTwo: public GameState {
    private:
        Sprite* titleElements[3];
        ChooseTeam* player1ChoosePlayer;
        ChooseTeam* player2ChoosePlayer;
        SubState* activeSubState;
        void toggleActiveSubState();
        std::stack<SubState*> subStateStackLeft;
        std::stack<SubState*> subStateStackRight;
        Team* team1 = nullptr;
        Team* team2 = nullptr;
        // Start Fight Anim
        bool startFightAnim = false;
        int startFightAnimTimer;

    public:
        TwoVsTwo(Screen* screen);
        ~TwoVsTwo();
        void keyInput(int key);
        void update(int deltaTime);
        GameState* getNextState();
        void startFight(Team* team, float start);
        void abortFight(float start);
};

#endif // TWOVSTWO_H

