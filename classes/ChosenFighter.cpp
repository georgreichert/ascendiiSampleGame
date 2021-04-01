#include "../headers/fightclub.h"

ChosenFighter::ChosenFighter(Screen* screen, OneVsOne* parentState, Fighter* fighter, float start) : SubState (screen, start, 0.5f, 9, 30) {
    this->fighter = fighter;
    this->parentState = parentState;
    parentState->startFight(fighter, start);
}

ChosenFighter::~ChosenFighter() {

}

void ChosenFighter::draw(int deltaTime) {
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

    //PIC
    Sprite* sprite = this->fighter->getSprite();
    currentRow = this->startLine + (this->height - sprite->getHeight()) / 2;
    sprite->draw(screen, leftMostIndex + (width - sprite->getWidth()) / 2, currentRow);
}

void ChosenFighter::keyInput(int key) {
    if (this->focused) {
        switch (key) {
            case KEY_UP:
                break;
            case KEY_DOWN:
                break;
            case KEY_SPACE:
                parentState->startFight(fighter, start);
                break;
            case KEY_ESC:
                this->parentState->abortFight(this->start);
                this->leave = true;
                break;
            default:
                break;
        }
    }
}
