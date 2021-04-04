#include "headers/fightclub.h"

int main() {
    srand((unsigned)time(0));
    DebugLog::reset();
    Screen* screen = new Screen("Fight Club");
    screen->fullScreen();
    int key = -1;
    bool pressed = false;
    int deltaTime = 0;
    std::stack<GameState*> stateStack;
    stateStack.push(new MainMenu(screen));

    while (1) {
        deltaTime = Time::getDeltaTime();
        Input::update(deltaTime);

        if (Input::getKeyDown(VK_SPACE) || Input::getKeyDown(VK_RETURN)) {
            key = KEY_SPACE;
        } else if (Input::getKeyDown(VK_ESCAPE)) {
            key = KEY_ESC;
        } else if (Input::getKeyDown(VK_UP)) {
            key = KEY_UP;
        } else if (Input::getKeyDown(VK_DOWN)) {
            key = KEY_DOWN;
        } else if (Input::getKeyDown(VK_LEFT)) {
            key = KEY_LEFT;
        } else if (Input::getKeyDown(VK_RIGHT)) {
            key = KEY_RIGHT;
        } else if (Input::getKeyDown(KEY_BLOCK_PLAYER_1)) {
            key = KEY_BLOCK_PLAYER_1;
        } else if (Input::getKeyDown(KEY_ABILITY_2_PLAYER_1)) {
            key = KEY_ABILITY_2_PLAYER_1;
        } else if (Input::getKeyDown(KEY_ABILITY_1_PLAYER_1)) {
            key = KEY_ABILITY_1_PLAYER_1;
        } else if (Input::getKeyDown(KEY_ABILITY_1_PLAYER_2)) {
            key = KEY_ABILITY_1_PLAYER_2;
        } else if (Input::getKeyDown(KEY_ABILITY_2_PLAYER_2)) {
            key = KEY_ABILITY_2_PLAYER_2;
        } else if (Input::getKeyDown(KEY_BLOCK_PLAYER_2)) {
            key = KEY_BLOCK_PLAYER_2;
        } else {
            key = -1;
        }
        stateStack.top()->keyInput(key);

        GameState* next = stateStack.top()->getNextState();
        if (next != nullptr) {
            stateStack.push(next);
        }
        if (stateStack.top()->leaveStatus()) {
            delete stateStack.top();
            stateStack.pop();
        }
        if (stateStack.empty()) {
            break;
        }
        screen->clear();
        stateStack.top()->update(deltaTime);
        screen->write(std::to_string(1000 / deltaTime) + " FPS", 0, 0, COLOR_WHITE);
        screen->draw();
    }

    while(!stateStack.empty()) {
        delete stateStack.top();
        stateStack.pop();
    }
    Database::destroy();
    delete screen;

}
