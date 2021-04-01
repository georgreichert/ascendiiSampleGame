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

    public:
        Fighter(std::string name, float maxHP, float baseDMG, float baseDEF, float blockBonus, Ability* ab1, Ability* ab2, Sprite* sprite = nullptr);
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
};

#endif // FIGHTER_H
