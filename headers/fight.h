#ifndef FIGHT_H
#define FIGHT_H

class Fight : public GameState {
    private:
        Fighter* fighter1;
        Fighter* fighter2;
        bool fighter2Copy = false;
        int turnIndex;
        // hit Animation
        bool hitAnim = false;
        int hitAnimFighterIndex;
        int hitAnimAbilityIndex;
        int hitAnimTimer;
        MoveAnimation* hitMoveAnim = nullptr;
        MoveAnimation* winAnim = nullptr;
        bool waitForEnd = false;
        int endTimer = 0;
        Sprite* hitSprite;
        bool aiPause = false;
        int aiPauseTimer = 0;

    public:
        Fight(Screen* screen, Fighter* fighter1, Fighter* fighter2);
        ~Fight();
        void update(int deltaTime);
        void keyInput(int key);
        void hit(int fighterIndex, int abilityIndex);
};

#endif // FIGHT_H
