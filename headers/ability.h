#ifndef ABILITY_H
#define ABILITY_H

class Ability {
    private:
        float power;
        float defense;
        float random;
        std::string name;

    public:
        Ability(std::string name, float power = 1.0, float defense = 1.0, float random = 0.2);
        float getPower();
        float getDefense();
        float getRandom();
        std::string getName();
};

#endif // ABILITY_H
