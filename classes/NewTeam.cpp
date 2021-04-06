#include "../headers/fightclub.h"

NewTeam::NewTeam(Screen* screen, GameState* parentState, float start) : SubState (screen, start, 0.5f, 9, 30) {
    this->fighters = Database::getFighters();
    this->parentState = parentState;
    this->menu = new NewTeamMenu(screen);
}

NewTeam::~NewTeam() {
    delete this->menu;
}

void NewTeam::update(int deltaTime) {
    int currentRow = this->startLine;
    int screenWidth = this->screen->getWidth();
    int leftMostIndex = screenWidth * this->start;
    int width = screenWidth * this->width;

    //menu
    this->menu->draw(leftMostIndex + width/2, currentRow + 5);

    // BORDER
    int margin = 3;
    int color = this->focused ? COLOR_GREEN : COLOR_RED;
    this->screen->horizontalLine(leftMostIndex + margin, currentRow, width - 2 * margin, color);
    this->screen->horizontalLine(leftMostIndex + margin, currentRow + this->height - 1, width - 2 * margin, color);
    this->screen->verticalLine(leftMostIndex + margin, currentRow, this->height, color);
    this->screen->verticalLine(leftMostIndex + width - margin, currentRow, this->height, color);
}

void NewTeam::keyInput(int key) {
    ((MenuTextInput*)this->menu->getMenuElement(0))->keyInput();
    if (Input::getKeyDown(VK_DOWN)) {
        this->menu->next();
    } else if (Input::getKeyDown(VK_UP)) {
        this->menu->prev();
    } else if (Input::getKeyDown(VK_RETURN) || Input::getKeyDown(VK_SPACE)) {
        this->menu->select();
    } else if (Input::getKeyDown(VK_ESCAPE)) {
        this->leave = true;
    }
}
