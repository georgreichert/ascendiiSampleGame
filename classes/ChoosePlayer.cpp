#include "../headers/fightclub.h"

ChoosePlayer::~ChoosePlayer() {
    delete this->profilePic;
    delete this->plusSign;
    delete this->questionMark;
    for (int i = 0; i < this->numberOfMenuElements; i++) {
        delete this->menuElements[i];
    }
}

ChoosePlayer::ChoosePlayer(Screen* screen, OneVsOne* parentState, bool playerType, float start) : SubState (screen, start, 0.5f, 9, 30) {
    std::string profilePic[9] = {
        "##############",
        "##          ##",
        "##          ##",
        "##          ##",
        "##          ##",
        "##          ##",
        "##          ##",
        "##          ##",
        "##############"
    };
    this->profilePic = new Sprite(profilePic, COLOR_YELLOW, profilePic[0].length(), 9);

    std::string plusSign[3] = {
        "  ##  ",
        "######",
        "  ##  "
    };
    this->plusSign = new Sprite(plusSign, COLOR_GREEN, plusSign[0].length(), 3);

    std::string questionMark[7] = {
        " #### ",
        "#   ##",
        "    ##",
        "  ### ",
        "  ##  ",
        "      ",
        "  ##  "
    };
    this->questionMark = new Sprite(questionMark, COLOR_RED, questionMark[0].length(), 7);

    this->playerType = playerType;
    this->parentState = parentState;

    std::string newPlayer[1] = "New Fighter";
    this->menuElements[0] = new MenuElement(new Sprite(newPlayer, COLOR_WHITE, newPlayer[0].length(), 1), false);
    std::string choosePlayer[1] = "Choose Fighter";
    this->menuElements[1] = new MenuElement(new Sprite(choosePlayer, COLOR_WHITE, choosePlayer[0].length(), 1), false);
    std::string aiMode[1] = "Mode: AI";
    this->menuElements[2] = new MenuElement(new Sprite(aiMode, COLOR_WHITE, aiMode[0].length(), 1), false);
    std::string humanMode[1] = "Mode: Player";
    this->menuElements[3] = new MenuElement(new Sprite(humanMode, COLOR_WHITE, humanMode[0].length(), 1), false);
}

void ChoosePlayer::keyInput(int key) {
    if (this->focused) {
        MenuElement* temp;
        switch (key) {
            case KEY_UP:
                if (this->cursorPosition > 0) {
                    this->menuElements[cursorPosition]->toggleActive();
                    this->cursorPosition--;
                    this->menuElements[cursorPosition]->toggleActive();
                }
                break;
            case KEY_DOWN:
                if (cursorPosition < 2) {
                    this->menuElements[cursorPosition]->toggleActive();
                    this->cursorPosition++;
                    this->menuElements[cursorPosition]->toggleActive();
                }
                break;
            case KEY_SPACE:
                switch (cursorPosition) {
                    case 0:
                        this->nextState = new NewFighter(this->screen, this->start);
                        break;
                    case 1:
                        this->nextState = new ChooseFighter(this->screen, this->parentState, this->start);
                        break;
                    case 2:
                        this->playerType = !this->playerType;
                        this->menuElements[2]->toggleActive();
                        temp = this->menuElements[2];
                        this->menuElements[2] = this->menuElements[3];
                        this->menuElements[3] = temp;
                        this->menuElements[2]->toggleActive();
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

void ChoosePlayer::update(int deltaTime) {
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

    // PROFILE PIC
    currentRow += 4;
    int picIndex = this->cursorPosition == 0 ? 0 : 1;
    int originX = leftMostIndex + (width - this->profilePic->getWidth()) / 2;
    this->profilePic->draw(this->screen, originX, currentRow);

    // PIC CONTENT
    if (this->cursorPosition == 0) {
        currentRow += 3;
        originX = leftMostIndex + (width - this->plusSign->getWidth()) / 2;
        this->plusSign->draw(this->screen, originX, currentRow);
        currentRow += 10;
    } else if (this->cursorPosition >= 1) {
        currentRow += 1;
        originX = leftMostIndex + (width - this->questionMark->getWidth()) / 2;
        this->questionMark->draw(this->screen, originX, currentRow);
        currentRow += 12;
    }

    // NEW FIGHTER
    originX = leftMostIndex + (width - this->menuElements[0]->getWidth()) / 2;
    this->menuElements[0]->draw(this->screen, originX, currentRow);
    // CHOOSE FIGHTER
    currentRow += 2;
    originX = leftMostIndex + (width - this->menuElements[1]->getWidth()) / 2;
    this->menuElements[1]->draw(this->screen, originX, currentRow);
    // MODE
    currentRow += 2;
    originX = leftMostIndex + (width - this->menuElements[2]->getWidth()) / 2;
    this->menuElements[2]->draw(this->screen, originX, currentRow);
}

void ChoosePlayer::toggleFocus() {
    this->focused = !this->focused;
    this->menuElements[this->cursorPosition]->toggleActive();
}

bool ChoosePlayer::getPlayerType() {
    return this->playerType;
}
