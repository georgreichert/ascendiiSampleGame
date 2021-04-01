#ifndef ONEVSONE_H
#define ONEVSONE_H

#include "fightclub.h"

class OneVsOne: public GameState {
    private:
        Sprite* titleElements[3];
        ChoosePlayer* player1ChoosePlayer;
        ChoosePlayer* player2ChoosePlayer;
        SubState* activeSubState;
        void toggleActiveSubState();
        std::stack<SubState*> subStateStackLeft;
        std::stack<SubState*> subStateStackRight;
        Fighter* fighter1 = nullptr;
        Fighter* fighter2 = nullptr;
        // Start Fight Anim
        bool startFightAnim = false;
        int startFightAnimTimer;

    public:
        OneVsOne(Screen* screen);
        ~OneVsOne();
        void keyInput(int key);
        void update(int deltaTime);
        GameState* getNextState();
        void startFight(Fighter* fighter, float start);
        void abortFight(float start);
};

#endif // ONEVSONE_H
