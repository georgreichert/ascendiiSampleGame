#include "headers/fightclub.h"

int main() {
    srand((unsigned)time(0));
    DebugLog::reset();
    Screen* screen = new Screen();
    screen->fullScreen();
    int key = -1;
    bool pressed = false;
    int deltaTime = 0;
    std::stack<GameState*> stateStack;
    stateStack.push(new MainMenu(screen));

    while (1) {
        deltaTime = Time::getDeltaTime();

        if (GetAsyncKeyState(VK_ESCAPE)) {
            key = KEY_ESC;
        } else if (GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_RETURN)) {
            key = KEY_SPACE;
        } else if (GetAsyncKeyState(VK_UP)) {
            key = KEY_UP;
        } else if (GetAsyncKeyState(VK_DOWN)) {
            key = KEY_DOWN;
        } else if (GetAsyncKeyState(VK_LEFT)) {
            key = KEY_LEFT;
        } else if (GetAsyncKeyState(VK_RIGHT)) {
            key = KEY_RIGHT;
        } else if (GetAsyncKeyState('A')) {
            key = 'A';
        } else if (GetAsyncKeyState('S')) {
            key = 'S';
        } else if (GetAsyncKeyState('D')) {
            key = 'D';
        } else if (GetAsyncKeyState('J')) {
            key = 'J';
        } else if (GetAsyncKeyState('K')) {
            key = 'K';
        } else if (GetAsyncKeyState('L')) {
            key = 'L';
        } else {
            pressed = false;
            key = -1;
        }
        if (!pressed && key != -1) {
            stateStack.top()->keyInput(key);
            pressed = true;
        }
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
