#include "../headers/fightclub.h"

NewFighter::NewFighter(Screen* screen, float start) : SubState (screen, start, 0.5f, 9, 30) {
    this->abilities = Database::getAbilities();

}

NewFighter::~NewFighter() {

}

void NewFighter::keyInput(int key) {
    if (this->focused) {
        //MenuElement* temp;
        switch (key) {
            case KEY_UP:
                if (this->cursorPosition > 0) {
//                    this->menuElements[cursorPosition]->toggleActive();
//                    this->cursorPosition--;
//                    this->menuElements[cursorPosition]->toggleActive();
                }
                break;
            case KEY_DOWN:
                if (cursorPosition < 2) {
//                    this->menuElements[cursorPosition]->toggleActive();
//                    this->cursorPosition++;
//                    this->menuElements[cursorPosition]->toggleActive();
                }
                break;
            case KEY_SPACE:
                switch (cursorPosition) {
                    case 0:
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    default:
                        break;
                }
                break;
            case KEY_ESC:
                this->leave = true;
                break;
            default:
                break;
        }
    }
}

void NewFighter::update(int deltaTime) {
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
}
