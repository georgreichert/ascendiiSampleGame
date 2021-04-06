#ifndef TEAMFIGHT_H
#define TEAMFIGHT_H

class TeamFight : public GameState {
    private:
        Team* team1;
        Team* team2;
        Fighter* fighters[4];
        bool fightersCopy[4] = {false, false, false, false};
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
        bool attackIndex = 0;

    public:
        TeamFight(Screen* screen, Team* team1, Team* team2);
        ~TeamFight();
        void update(int deltaTime);
        void keyInput(int key);
        void hit(int fighterIndex, int abilityIndex);
};

#endif // TEAMFIGHT_H
