#include "../headers/fightclub.h"

OneVsOne::OneVsOne(Screen* screen) : GameState(screen) {
    std::string player[5] = {
        "####  ##      ####  ##  ## ###### #### ",
        "## ## ##     ##  ##  ####  ##     ## ##",
        "####  ##     ######   ##   ####   #### ",
        "##    ##     ##  ##   ##   ##     ## ##",
        "##    ###### ##  ##   ##   ###### ##  #"
    };
    this->titleElements[0] = new Sprite(player, COLOR_YELLOW, player[0].length(), 5);

    std::string ai[5] = {
        " ####  ##",
        "##  ## ##",
        "###### ##",
        "##  ## ##",
        "##  ## ##"
    };
    this->titleElements[1] = new Sprite(ai, COLOR_YELLOW, ai[0].length(), 5);

    std::string vs[5] = {
        "         ",
        "         ",
        "#   # ###",
        " # #  \\\\ ",
        "  #  ### "
    };
    this->titleElements[2] = new Sprite(vs, COLOR_CYAN, vs[0].length(), 5);

    this->player1ChoosePlayer = new ChoosePlayer(this->screen, this);
    this->subStateStackLeft.push(player1ChoosePlayer);
    this->subStateStackLeft.top()->toggleFocus();
    this->activeSubState = this->subStateStackLeft.top();

    this->player2ChoosePlayer = new ChoosePlayer(this->screen, this, false, 0.5f);
    this->subStateStackRight.push(player2ChoosePlayer);
}

OneVsOne::~OneVsOne() {
    for (int i = 0; i < 3; i++) {
        delete this->titleElements[i];
    }
    while (!this->subStateStackLeft.empty()) {
        delete this->subStateStackLeft.top();
        this->subStateStackLeft.pop();
    }
    while (!this->subStateStackRight.empty()) {
        delete this->subStateStackRight.top();
        this->subStateStackRight.pop();
    }
}

void OneVsOne::keyInput(int key) {
    if (!this->startFightAnim) {
        switch (key) {
            case KEY_ESC:
                this->activeSubState->keyInput(key);
                if (this->activeSubState->leaveStatus()) {
                    if (this->subStateStackLeft.top() == activeSubState) {
                        delete subStateStackLeft.top();
                        this->subStateStackLeft.pop();
                        if(this->subStateStackLeft.empty()) {
                            this->activeSubState = nullptr;
                            this->leave = true;
                        } else {
                            this->activeSubState = this->subStateStackLeft.top();
                        }
                    } else {
                        delete subStateStackRight.top();
                        this->subStateStackRight.pop();
                        if(this->subStateStackRight.empty()) {
                            this->activeSubState = nullptr;
                            this->leave = true;
                        } else {
                            this->activeSubState = this->subStateStackRight.top();
                        }
                    }
                }
                break;
            case KEY_RIGHT:
                toggleActiveSubState();
                break;
            case KEY_LEFT:
                toggleActiveSubState();
                break;
            default:
                this->activeSubState->keyInput(key);
                break;
        }
        if (activeSubState != nullptr) {
            SubState* nextSubState = this->activeSubState->getNextState();
            if (nextSubState != nullptr) {
                if (this->subStateStackLeft.top() == activeSubState) {
                    this->subStateStackLeft.push(nextSubState);
                    this->activeSubState = this->subStateStackLeft.top();
                } else {
                    this->subStateStackRight.push(nextSubState);
                    this->activeSubState = this->subStateStackRight.top();
                }
                this->activeSubState->toggleFocus();
            }
        }
    }
}

void OneVsOne::update(int deltaTime) {
    int currentRow = 1;
    int width = this->screen->getWidth();

    // PLAYER 1
    int elementIndex = this->player1ChoosePlayer->getPlayerType() ? 0 : 1;
    int length = this->titleElements[elementIndex]->getWidth();
    int originX = width / 4 - length / 2 ;
    this->titleElements[elementIndex]->draw(screen, originX, currentRow);

    // VS
    length = this->titleElements[2]->getWidth();
    originX = (width - length) / 2 ;
    this->titleElements[2]->draw(screen, originX, currentRow);

    // PLAYER 2
    elementIndex = this->player2ChoosePlayer->getPlayerType() ? 0 : 1;
    length = this->titleElements[elementIndex]->getWidth();
    originX = width * 3 / 4 - length / 2 ;
    this->titleElements[elementIndex]->draw(screen, originX, currentRow);

    // Lines
    currentRow += 6;
    this->screen->horizontalLine(0, currentRow, width, COLOR_RED);

    // SubStates
    this->subStateStackLeft.top()->update(deltaTime);
    this->subStateStackRight.top()->update(deltaTime);

    currentRow += 33;
    // Line
    this->screen->horizontalLine(0, currentRow, width, COLOR_RED);

    if (this->startFightAnim) {
        this->startFightAnimTimer += deltaTime;
        if (this->startFightAnimTimer < 1000) {
            Sprite* three = Database::getThreeTwoOne(0);
            three->draw(screen, (width - three->getWidth()) / 2, 10, false, ' ');
        } else if (this->startFightAnimTimer < 2000) {
            Sprite* two = Database::getThreeTwoOne(1);
            two->draw(screen, (width - two->getWidth()) / 2, 10, false, ' ');
        } else if (this->startFightAnimTimer < 3000) {
            Sprite* one = Database::getThreeTwoOne(2);
            one->draw(screen, (width - one->getWidth()) / 2, 10, false, ' ');
        } else {
            this->startFightAnim = false;
            this->nextState = new Fight(screen, this->fighter1, this->fighter2);
        }
    }
}

void OneVsOne::toggleActiveSubState() {
    this->activeSubState->toggleFocus();
    this->activeSubState = this->activeSubState == this->subStateStackLeft.top() ? this->subStateStackRight.top() : this->subStateStackLeft.top();
    this->activeSubState->toggleFocus();
}

void OneVsOne::startFight(Fighter* fighter, float start) {
    if (start == 0.0f) {
        this->fighter1 = fighter;
    } else {
        this->fighter2 = fighter;
    }
    if (this->fighter1 != nullptr && this->fighter2 != nullptr) {
        DebugLog::log("Fight starts now");
        this->startFightAnim = true;
        this->startFightAnimTimer = 0;
    }
}

void OneVsOne::abortFight(float start) {
    if (start == 0.0f) {
        this->fighter1 = nullptr;
    } else {
        this->fighter2 = nullptr;
    }
}
