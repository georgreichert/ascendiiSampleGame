#ifndef DATABASE_H
#define DATABASE_H

#include "fightclub.h"

class Database {
    private:
        static std::vector<Ability*> abilities;
        static std::vector<Fighter*> fighters;
        static Sprite* hitSprite;
        static Sprite* threeTwoOne[3];
        static Sprite* winner;
        static bool initialized;
        static void initialize();

    public:
        static std::vector<Ability*> getAbilities();
        static Ability* getAbility(std::string name);
        static std::vector<Fighter*> getFighters();
        static Fighter* getFighter(std::string name);
        static Sprite* getHitSprite();
        static Sprite* getThreeTwoOne(int index);
        static Sprite* getWinner();
        static void destroy();
};

#endif // DATABASE_H
