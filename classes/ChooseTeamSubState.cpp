#include "../headers/fightclub.h"


ChooseTeamSubState::ChooseTeamSubState(Screen* screen, TwoVsTwo* parentState, bool playerType, float start) : SubState (screen, start, 0.5f, 9, 30) {
    this->teams = Database::getTeams();
    this->parentState = parentState;
    for (Team* te : this->teams) {
        std::string name[1];
        name[0] = te->getName();
        this->menuElements.push_back(new MenuElement(new Sprite(name, COLOR_WHITE, name[0].length(), 1)));
    }
    this->menuElements.front()->toggleActive();
    this->playerType = playerType;
}

ChooseTeamSubState::~ChooseTeamSubState() {
    for (MenuElement* me : this->menuElements) {
        delete me;
    }
}

void ChooseTeamSubState::keyInput(int key) {
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
                this->teams[this->cursorPosition]->setPlayerType(this->playerType);
                this->nextState = new ChosenTeam(this->screen, this->parentState, this->teams[this->cursorPosition], this->start);
                break;
            case KEY_ESC:
                this->leave = true;
                break;
            default:
                break;
        }
    }
}

void ChooseTeamSubState::update(int deltaTime) {
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

    Team* activeTeam = this->teams[this->cursorPosition];
    currentRow = this->startLine + this->height - 4;
    int percent = activeTeam->getVictories() + activeTeam->getDefeats() != 0 ? 100 * activeTeam->getVictories()
                / (activeTeam->getVictories() + activeTeam->getDefeats()) : 0;
    screen->write("Wins: " + std::to_string(activeTeam->getVictories()) +
            " (" + std::to_string(percent) + "%)",leftMostIndex +  width / 4 - 4, currentRow);
    screen->write("Defeats: " + std::to_string(activeTeam->getDefeats()), leftMostIndex + 3 * width / 4 - 6, currentRow);
    std::string name = this->teams[this->cursorPosition]->getFighter(0)->getName();
    screen->write(name, leftMostIndex + (width - name.length()) / 2, currentRow - 1, COLOR_YELLOW);
    name = this->teams[this->cursorPosition]->getFighter(1)->getName();
    screen->write(name, leftMostIndex +  (width - name.length()) / 2, currentRow + 1, COLOR_YELLOW);
    screen->write("&", leftMostIndex + width / 2, currentRow, COLOR_CYAN);
}

