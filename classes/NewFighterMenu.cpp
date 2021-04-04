#include "../headers/fightclub.h"

NewFighterMenu::NewFighterMenu(Screen* screen) : Menu(screen) {
    std::string name[1] = {"Name: "};
    this->menuElements.push_back(new MenuTextInput(new Sprite(name, COLOR_RED, name[0].length(), 1), "Name: ", "", 20, true));

    std::string aiStyle1[1] = {"AI Style: Standard"};
    std::string aiStyle2[1] = {"AI Style: Aggressive"};
    std::string aiStyle3[1] = {"AI Style: Defensive"};
    this->aiStyles.push_back(new MenuElement(new Sprite(aiStyle1, COLOR_WHITE, aiStyle1[0].length(), 1)));
    this->aiStyles.push_back(new MenuElement(new Sprite(aiStyle2, COLOR_RED, aiStyle2[0].length(), 1), true));
    this->aiStyles.push_back(new MenuElement(new Sprite(aiStyle3, COLOR_RED, aiStyle3[0].length(), 1), true));
    this->menuElements.push_back(this->aiStyles[0]);

    for (Ability* ab : Database::getAbilities()) {
        std::string abilityString[1] = {"Ability 1: " + ab->getName()};
        this->ability1Elements.push_back(new MenuElement(new Sprite(abilityString, COLOR_RED, abilityString[0].length(), 1), true));
    }
    this->ability1Elements[0]->toggleActive();
    this->menuElements.push_back(this->ability1Elements[0]);

    for (Ability* ab : Database::getAbilities()) {
        std::string abilityString[1] = {"Ability 2: " + ab->getName()};
        this->ability2Elements.push_back(new MenuElement(new Sprite(abilityString, COLOR_RED, abilityString[0].length(), 1), true));
    }
    this->ability2Elements[0]->toggleActive();
    this->menuElements.push_back(this->ability2Elements[0]);

    std::string create[1] = {"Create"};
    this->menuElements.push_back(new MenuElement(new Sprite(create, COLOR_WHITE, create[0].length(), 1)));

}

NewFighterMenu::~NewFighterMenu() {
    delete menuElements[0];
    for (MenuElement* ai : aiStyles) {
        delete ai;
    }
    for (MenuElement* ab : ability1Elements) {
        delete ab;
    }
    for (MenuElement* ab : ability2Elements) {
        delete ab;
    }
    delete menuElements[4];
}

void NewFighterMenu::draw(int originX, int originY) {
    for(MenuElement* me : this->menuElements) {
        me->draw(this->screen, originX - (me->getWidth() / 2), originY);
        originY += 2;
    }
}

void NewFighterMenu::select() {
    if (this->cursorPosition == 1) {
        if (this->aiStylePosition < 2) {
            this->aiStylePosition++;
        } else {
            this->aiStylePosition = 0;
        }
        this->menuElements[1] = this->aiStyles[aiStylePosition];
    }
    if (this->cursorPosition == 2) {
        if (this->ability1Position < this->ability1Elements.size() - 1) {
            this->ability1Position++;
        } else {
            this->ability1Position = 0;
        }
        this->menuElements[2] = this->ability1Elements[ability1Position];
    }
    if (this->cursorPosition == 3) {
        if (this->ability2Position < this->ability2Elements.size() - 1) {
            this->ability2Position++;
        } else {
            this->ability2Position = 0;
        }
        this->menuElements[3] = this->ability2Elements[ability2Position];
    }
    if (this->cursorPosition == 4) {
        if (!((MenuTextInput*)this->menuElements[0])->getVariable().empty()) {
            std::string fighterFace[28] = {
                "                                                            ",
                "                                                            ",
                "                           \|/                              ",
                "                        ##########                          ",
                "                    #################                       ",
                "                  #####################                     ",
                "                #########################                   ",
                "               ###########################                  ",
                "               #####  o  #######  o  #####                  ",
                "               ######   #########   ######                  ",
                "               ###########################                  ",
                "               ###########################                  ",
                "                #########################                   ",
                "                 #######################                    ",
                "                  ###### | | | | ######                     ",
                "                   ###################                      ",
                "                     ###############                        ",
                "                        #########                           ",
                "                         #######                            ",
                "                         #######                            ",
                "                     ###############                        ",
                "                    #################                       ",
                "                    ##   #######   ##                       ",
                "                  #####   #####   #####                     ",
                "                   ####    ###    ####                      ",
                "                           ###                              ",
                "                          #   #                             ",
                "                        ###   ###                           "
            };
            DecisionTree* decisionTree;
            switch (this->aiStylePosition) {
                case 0:
                    decisionTree = Database::getDecisionTree(0);
                    break;
                case 1:
                    decisionTree = Database::getDecisionTree(1);
                    break;
                case 2:
                    decisionTree = Database::getDecisionTree(2);
                    break;
                default:
                    decisionTree = Database::getDecisionTree(0);
                    break;
            }
            Database::addFighter(new Fighter(((MenuTextInput*)this->menuElements[0])->getVariable(),
                                                        100 + (rand() % 31 -15),
                                                        1.0f * (rand() % 9 + 16),
                                                        0.05f * (rand() % 15 + 14),
                                                        0.1f * (rand() % 13 + 10),
                                                        Database::getAbilities()[this->ability1Position],
                                                        Database::getAbilities()[this->ability2Position],
                                                        new Sprite(fighterFace, COLOR_WHITE, fighterFace[0].length(), 28),
                                                        decisionTree
                                                        ));
            DebugLog::log(std::to_string(Database::getFighters().size()));
        }
    }
}
