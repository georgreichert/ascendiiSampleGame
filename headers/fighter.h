#ifndef FIGHTER_H
#define FIGHTER_H

class Fighter {
    private:
        std::string name;
        float maxHP;
        float currentHP;
        float baseDMG;
        float baseDEF;
        float blockBonus;
        bool blocking = false;
        Ability* abilities[2];
        float currentDMGfactor = 1.0;
        float currentDEFfactor = 1.0;
        float currentRandomModifier = 0.2;
        Sprite* sprite;
        int victories = 0;
        int defeats = 0;
        DecisionTree* decisionTree;
        bool playerType = PLAYER_TYPE_AI;

    public:
        Fighter(std::string name, float maxHP, float baseDMG, float baseDEF, float blockBonus,
                    Ability* ab1, Ability* ab2, Sprite* sprite, DecisionTree* decisionTree);
        ~Fighter();
        std::string getName();
        float getMaxHP();
        float getCurrentHP();
        float getBaseDMG();
        float getBaseDEF();
        float getBlockBonus();
        bool isBlocking();
        float takeHit(float DMG);
        float hit(int ability);
        void block();
        Ability* getAbility(int index);
        Sprite* getSprite();
        void heal();
        Fighter* clone();
        int getVictories();
        int getDefeats();
        void victory();
        void defeat();
        void setPlayerType(bool playerType);
        bool getPlayerType();
        char decide();
};

#endif // FIGHTER_H
