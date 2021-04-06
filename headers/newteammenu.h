#ifndef NEWTEAMMENU_H
#define NEWTEAMMENU_H

#include "fightclub.h"

class NewTeamMenu : public Menu {
    private:
        std::vector<MenuElement*> fighter1Elements;
        std::vector<MenuElement*> fighter2Elements;
        std::vector<Fighter*> fighters;
        int ability1Position = 0;
        int ability2Position = 0;

    public:
        NewTeamMenu(Screen* screen);
        ~NewTeamMenu();
        void draw(int originX, int originY);
        void select();
};

#endif // NEWTEAMMENU_H
