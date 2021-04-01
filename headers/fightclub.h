#ifndef FIGHTCLUB_H
#define FIGHTCLUB_H

#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <list>
#include <sstream>
#include <stack>
#include <vector>
#include <winuser.h>
#include <chrono>

#define KEY_UP    720
#define KEY_LEFT  750
#define KEY_RIGHT 770
#define KEY_DOWN  800
#define KEY_ESC   270
#define KEY_ENTER 130
#define KEY_SPACE 320

#define COLOR_YELLOW    14
#define COLOR_RED       12
#define COLOR_CYAN      11
#define COLOR_WHITE     15
#define COLOR_GREEN     10
#define COLOR_BLUE      9
#define COLOR_PINK      13
#define BG_COLOR_GREEN  160
#define BG_COLOR_RED    192
#define BG_COLOR_YELLOW 224

#include "debuglog.h"
#include "screen.h"
#include "sprite.h"
#include "ability.h"
#include "fighter.h"
#include "database.h"
#include "gamestate.h"
#include "menuelement.h"
#include "substate.h"
#include "mainmenu.h"
class OneVsOne;
#include "chooseplayer.h"
#include "newfighter.h"
#include "choosefighter.h"
#include "chosenfighter.h"
#include "onevsone.h"
#include "fight.h"

#endif // FIGHTCLUB_H
