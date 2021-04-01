#include "headers/fightclub.h"

int main() {
    srand((unsigned)time(0));
    DebugLog::reset();
    Screen* screen = new Screen();
    int key = -1;
    bool pressed = false;
    unsigned long long int lastFrame = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    unsigned long long int thisFrame;
    int deltaTime = 0;
    std::stack<GameState*> stateStack;
    stateStack.push(new MainMenu(screen));
    screen->flush();
    stateStack.top()->draw(deltaTime);
    screen->draw();
    int throttledDeltaTime = 21;

    while (1) {
        thisFrame = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        deltaTime = thisFrame - lastFrame;
        lastFrame = thisFrame;
        throttledDeltaTime += deltaTime;

        if (throttledDeltaTime > 20) {
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
            screen->updateWidth();
            screen->flush();
            stateStack.top()->draw(throttledDeltaTime);
            screen->write(std::to_string(1000 / throttledDeltaTime) + " FPS", 0, 0, COLOR_WHITE);
            screen->draw();
            throttledDeltaTime = 0;
        }
    }

    while(!stateStack.empty()) {
        delete stateStack.top();
        stateStack.pop();
    }
    Database::destroy();
    delete screen;

}
