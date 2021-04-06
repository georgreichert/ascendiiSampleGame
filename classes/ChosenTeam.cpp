#include "../headers/fightclub.h"

ChosenTeam::ChosenTeam(Screen* screen, TwoVsTwo* parentState, Team* team, float start) : SubState (screen, start, 0.5f, 9, 30) {
    this->team = team;
    this->parentState = parentState;
    parentState->startFight(team, start);
}

ChosenTeam::~ChosenTeam() {

}

void ChosenTeam::update(int deltaTime) {
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

    //NAMES
    currentRow = this->startLine + this->height / 2;
    std::string name = this->team->getFighter(0)->getName();
    this->screen->write(name, leftMostIndex + (width - name.length()) / 2, currentRow - 2, COLOR_YELLOW);
    name = this->team->getFighter(1)->getName();
    this->screen->write(name, leftMostIndex + (width - name.length()) / 2, currentRow + 2, COLOR_YELLOW);
    this->screen->write("&", leftMostIndex + width / 2, currentRow, COLOR_CYAN);
}

void ChosenTeam::keyInput(int key) {
    if (this->focused) {
        switch (key) {
            case KEY_UP:
                break;
            case KEY_DOWN:
                break;
            case KEY_SPACE:
                parentState->startFight(team, start);
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

