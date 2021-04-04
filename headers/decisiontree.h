#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "fightclub.h"

class DecisionTree {
    private:

    public:
        virtual char decide(Fighter* fighter) = 0;
};

#endif // DECISIONTREE_H
