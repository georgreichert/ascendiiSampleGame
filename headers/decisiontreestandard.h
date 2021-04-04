#ifndef DECISIONTREESTANDARD_H
#define DECISIONTREESTANDARD_H

#include "fightclub.h"

class DecisionTreeStandard : public DecisionTree {
    private:

    public:
        char decide(Fighter* fighter);
};

#endif // DECISIONTREESTANDARD_H
