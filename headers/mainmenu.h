#ifndef MAINMENU_H
#define MAINMENU_H

#include "fightclub.h"

class MainMenu: public GameState {
    private:
        int cursorPosition = 0;
        Sprite* fight;
        Sprite* club;
        MenuElement* menuElements[3];
        bool beginAnimation = true;
        int beginAnimationTimer = 0;
        MoveAnimation* beginAnimationFight;
        MoveAnimation* beginAnimationClub;

    public:
        MainMenu(Screen* screen);
        ~MainMenu();
        void keyInput(int key);
        void update(int deltaTime);
        GameState* getNextState();
};

#endif // MAINMENU_H
