#ifndef NEWFIGHTERMENU_H
#define NEWFIGHTERMENU_H

#include "fightclub.h"

class NewFighterMenu : public Menu {
    private:
        std::vector<MenuElement*> aiStyles;
        std::vector<MenuElement*> ability1Elements;
        std::vector<MenuElement*> ability2Elements;
        int aiStylePosition = 0;
        int ability1Position = 0;
        int ability2Position = 0;

    public:
        NewFighterMenu(Screen* screen);
        ~NewFighterMenu();
        void draw(int originX, int originY);
        void select();
};

#endif // NEWFIGHTERMENU_H
