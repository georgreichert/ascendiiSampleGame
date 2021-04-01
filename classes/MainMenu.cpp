#include "../headers/fightclub.h"

MainMenu::MainMenu(Screen* screen) : GameState(screen) {
    std::string fight[5] = {
        "###### ## ###### ##  ## ######",
        "##     ## ##     ##  ##   ##  ",
        "####   ## ##  ## ######   ##  ",
        "##     ## ##   # ##  ##   ##  ",
        "##     ## ###### ##  ##   ##  "
    };
    this->fight = new Sprite(fight, COLOR_YELLOW, fight[0].length(), 5);

    std::string club[5] = {
        "###### ##     ##  ## ##### ",
        "##     ##     ##  ## ##  ##",
        "##     ##     ##  ## ##### ",
        "##     ##     ##  ## ##  ##",
        "###### ###### ###### ##### "
    };
    this->club = new Sprite(club, COLOR_CYAN, club[0].length(), 5);

    std::string oneVone[4] {
        " ##              ##",
        "# #  #   # ###  # #",
        "  #   # #  \\\\     #",
        "  #    #  ###     #"
    };
    this->menuElements[0] = new MenuElement(new Sprite(oneVone, COLOR_RED, oneVone[0].length(), 4), true);

    std::string twoVtwo[4] {
        "####             ####",
        "  #   #   # ###    # ",
        " #     # #  \\\\    #  ",
        "####    #  ###   ####"
    };
    this->menuElements[1] = new MenuElement(new Sprite(twoVtwo, COLOR_WHITE, twoVtwo[0].length(), 4));

    std::string exit[4] {
        "#### #  # # #####",
        "#__   ##  #   #  ",
        "#     ##  #   #  ",
        "#### #  # #   #  "
    };
    this->menuElements[2] = new MenuElement(new Sprite(exit, COLOR_WHITE, exit[0].length(), 4));
}

void MainMenu::update(int deltaTime) {
    int currentRow = 7;
    int width = this->screen->getWidth();

    // FIGHT
    int originX = (width - this->fight->getWidth()) / 2 - 3;
    this->fight->draw(this->screen, originX, currentRow);

    // CLUB
    currentRow += 5;
    originX = (width - this->club->getWidth()) / 2 + 3;
    this->club->draw(this->screen, originX, currentRow);

    // 1 vs 1
    currentRow += 9;
    originX = (width - this->menuElements[0]->getWidth()) / 2;
    this->menuElements[0]->draw(this->screen, originX, currentRow);

    // 2 vs 2
    currentRow += 5;
    originX = (width - this->menuElements[1]->getWidth()) / 2;
    this->menuElements[1]->draw(this->screen, originX, currentRow);

    // EXIT
    currentRow += 5;
    originX = (width - this->menuElements[2]->getWidth()) / 2;
    this->menuElements[2]->draw(this->screen, originX, currentRow);
}

MainMenu::~MainMenu() {
    delete this->fight;
    delete this->club;
    for (int i = 0; i < 3; i++) {
        delete this->menuElements[i];
    }
}

void MainMenu::keyInput(int key) {
    switch (key) {
        case KEY_UP:
            if (cursorPosition > 0) {
                this->menuElements[cursorPosition]->toggleActive();
                cursorPosition--;
                this->menuElements[cursorPosition]->toggleActive();
            }
            break;
        case KEY_DOWN:
            if (cursorPosition < 2) {
                this->menuElements[cursorPosition]->toggleActive();
                cursorPosition++;
                this->menuElements[cursorPosition]->toggleActive();
            }
            break;
        case KEY_SPACE:
            switch (cursorPosition) {
                case 0:
                    this->nextState = new OneVsOne(this->screen);
                    break;
                case 1:
                    break;
                case 2:
                    this->leave = true;
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
