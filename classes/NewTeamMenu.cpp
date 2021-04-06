#include "../headers/fightclub.h"

NewTeamMenu::NewTeamMenu(Screen* screen) : Menu(screen) {
    this->fighters = Database::getFighters();

    std::string name[1] = {"Name: "};
    this->menuElements.push_back(new MenuTextInput(new Sprite(name, COLOR_RED, name[0].length(), 1), "Name: ", "", 20, true));

    for (Fighter* fi : Database::getFighters()) {
        std::string fighterString[1] = {"Fighter 1: " + fi->getName()};
        this->fighter1Elements.push_back(new MenuElement(new Sprite(fighterString, COLOR_RED, fighterString[0].length(), 1), true));
    }
    this->fighter1Elements[0]->toggleActive();
    this->menuElements.push_back(this->fighter1Elements[0]);

    for (Fighter* fi : Database::getFighters()) {
        std::string fighterString[1] = {"Fighter 2: " + fi->getName()};
        this->fighter2Elements.push_back(new MenuElement(new Sprite(fighterString, COLOR_RED, fighterString[0].length(), 1), true));
    }
    this->fighter2Elements[0]->toggleActive();
    this->menuElements.push_back(this->fighter2Elements[0]);

    std::string create[1] = {"Create"};
    this->menuElements.push_back(new MenuElement(new Sprite(create, COLOR_WHITE, create[0].length(), 1)));

}

NewTeamMenu::~NewTeamMenu() {
    delete menuElements[0];
    for (MenuElement* ab : this->fighter1Elements) {
        delete ab;
    }
    for (MenuElement* ab : this->fighter2Elements) {
        delete ab;
    }
    delete menuElements[3];
}

void NewTeamMenu::draw(int originX, int originY) {
    for(MenuElement* me : this->menuElements) {
        me->draw(this->screen, originX - (me->getWidth() / 2), originY);
        originY += 2;
    }
}

void NewTeamMenu::select() {
    if (this->cursorPosition == 1) {
        if (this->ability1Position < this->fighter1Elements.size() - 1) {
            this->ability1Position++;
        } else {
            this->ability1Position = 0;
        }
        this->menuElements[1] = this->fighter1Elements[ability1Position];
    }
    if (this->cursorPosition == 2) {
        if (this->ability2Position < this->fighter2Elements.size() - 1) {
            this->ability2Position++;
        } else {
            this->ability2Position = 0;
        }
        this->menuElements[2] = this->fighter2Elements[ability2Position];
    }
    if (this->cursorPosition == 3) {
        if (!((MenuTextInput*)this->menuElements[0])->getVariable().empty()) {
            Database::addTeam(new Team(this->fighters[this->ability1Position], this->fighters[this->ability2Position],
                                       ((MenuTextInput*)this->menuElements[0])->getVariable()));
        }
    }
}

