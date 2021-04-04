#ifndef FIGHTCLUB_H
#define FIGHTCLUB_H

#include <iostream>
#include <iomanip>
#include <list>
#include <stack>

#define KEY_ABILITY_1           1
#define KEY_ABILITY_2           2
#define KEY_BLOCK               3
#define KEY_ABILITY_1_PLAYER_1  68
#define KEY_ABILITY_2_PLAYER_1  83
#define KEY_BLOCK_PLAYER_1      65
#define KEY_ABILITY_1_PLAYER_2  74
#define KEY_ABILITY_2_PLAYER_2  75
#define KEY_BLOCK_PLAYER_2      76
#define PLAYER_TYPE_AI          false
#define PLAYER_TYPE_PLAYER      true

#include "../ascendii/ascendii.h"
#include "ability.h"
class DecisionTree;
#include "fighter.h"
#include "decisiontree.h"
#include "decisiontreestandard.h"
#include "decisiontreeaggressive.h"
#include "decisiontreedefensive.h"
#include "database.h"
#include "mainmenu.h"
class OneVsOne;
#include "chooseplayer.h"
#include "newfightermenu.h"
#include "newfighter.h"
#include "choosefighter.h"
#include "chosenfighter.h"
#include "onevsone.h"
#include "fight.h"

#endif // FIGHTCLUB_H
