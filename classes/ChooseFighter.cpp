#include "../headers/fightclub.h"


ChooseFighter::ChooseFighter(Screen* screen, OneVsOne* parentState, float start) : SubState (screen, start, 0.5f, 9, 30) {
    this->fighters = Database::getFighters();
    this->parentState = parentState;
    for (Fighter* fi : fighters) {
        std::string name[1];
        name[0] = fi->getName();
        this->menuElements.push_back(new MenuElement(new Sprite(name, COLOR_WHITE, name[0].length(), 1)));
    }
    this->menuElements.front()->toggleActive();
}

ChooseFighter::~ChooseFighter() {

}

void ChooseFighter::keyInput(int key) {
    if (this->focused) {
        //MenuElement* temp;
        switch (key) {
            case KEY_UP:
                if (this->cursorPosition > 0) {
                    this->menuElements[cursorPosition]->toggleActive();
                    this->cursorPosition--;
                    this->menuElements[cursorPosition]->toggleActive();
                }
                break;
            case KEY_DOWN:
                if (cursorPosition < this->menuElements.size() - 1) {
                    this->menuElements[cursorPosition]->toggleActive();
                    this->cursorPosition++;
                    this->menuElements[cursorPosition]->toggleActive();
                }
                break;
            case KEY_SPACE:
                this->nextState = new ChosenFighter(this->screen, this->parentState, this->fighters[this->cursorPosition], this->start);
                break;
            case KEY_ESC:
                this->leave = true;
                break;
            default:
                break;
        }
    }
}

void ChooseFighter::update(int deltaTime) {
    int currentRow = this->startLine;
    int screenWidth = this->screen->getWidth();
    int leftMostIndex = screenWidth * this->start;
    int width = screenWidth * this->width;

    // BORDER
    int margin = 3;
    int color = this->focused ? COLOR_GREEN : COLOR_RED;
    this->screen->horizontalLine(leftMostIndex + margin, currentRow, width - 2 * margin, color);
    this->screen->horizontalLine(leftMostIndex + margin, currentRow + this->height - 1, width - 2 * margin, color);
    this->screen->verticalLine(leftMostIndex + margin, currentRow, this->height, color);
    this->screen->verticalLine(leftMostIndex + width - margin, currentRow, this->height, color);

    // Menu Elements
    currentRow += 3;
    for (MenuElement* me : menuElements) {
        me->draw(this->screen, leftMostIndex + (width - me->getWidth()) / 2, currentRow);
        currentRow += 2;
    }

    Fighter* activeFighter = this->fighters[this->cursorPosition];
    currentRow = this->startLine + 3 * this->height / 4;
    int percent = activeFighter->getVictories() + activeFighter->getDefeats() != 0 ? 100 * activeFighter->getVictories()
                / (activeFighter->getVictories() + activeFighter->getDefeats()) : 0;
    screen->write("Wins: " + std::to_string(activeFighter->getVictories()) +
            " (" + std::to_string(percent) + "%)",leftMostIndex +  width / 4 - 4, currentRow - 2);
    screen->write("Defeats: " + std::to_string(activeFighter->getDefeats()), leftMostIndex + 3 * width / 4 - 6, currentRow - 2);
    screen->write("HP:  ", leftMostIndex + width / 3 - 13, currentRow, COLOR_RED);
    screen->horizontalLine(leftMostIndex + width / 3 - 8, currentRow, activeFighter->getMaxHP() * 2 / 10, BG_COLOR_GREEN, ' ');
    currentRow++;
    screen->write("Ability 1: " + activeFighter->getAbility(0)->getName(), leftMostIndex + width * 2 / 3 - 5, currentRow, COLOR_RED);
    currentRow++;
    screen->write("DMG: ", leftMostIndex + width / 3 - 13, currentRow, COLOR_RED);
    screen->horizontalLine(leftMostIndex + width / 3 - 8, currentRow, activeFighter->getBaseDMG() * 2 / 1.5f, BG_COLOR_RED, ' ');
    currentRow++;
    screen->write("Ability 2: " + activeFighter->getAbility(1)->getName(), leftMostIndex + width * 2 / 3 - 5, currentRow, COLOR_RED);
    currentRow++;
    screen->write("DEF: ", leftMostIndex + width / 3 - 13, currentRow, COLOR_RED);
    screen->horizontalLine(leftMostIndex + width / 3 - 8, currentRow, activeFighter->getBaseDEF() * 20, BG_COLOR_YELLOW, ' ');
}
