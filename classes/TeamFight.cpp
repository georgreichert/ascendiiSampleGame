#include "../headers/fightclub.h"

TeamFight::TeamFight(Screen* screen, Team* team1, Team* team2) : GameState(screen) {
    this->team1 = team1;
    this->team2 = team2;
    this->fighters[0] = team1->getFighter(0);
    this->fighters[1] = team1->getFighter(1);
    this->fighters[2] = team2->getFighter(0);
    this->fighters[3] = team2->getFighter(1);
    for (int i = 1; i < 4; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (fighters[i]->getName().compare(fighters[j]->getName()) == 0) {
                this->fighters[i] = fighters[i]->clone();
                this->fightersCopy[i] = true;
            }
        }
    }
    this->turnIndex = rand() % 4;
    this->hitSprite = Database::getHitSprite();
}

TeamFight::~TeamFight() {
    for (int i = 0; i < 4; i++) {
        this->fighters[i]->heal();
        this->fighters[i]->getSprite()->setColor(COLOR_WHITE);
        if (this->fightersCopy[i]) {
            delete fighters[i];
        }
    }
}

void TeamFight::update(int deltaTime) {
    if (this->hitAnim) {
        hitAnimTimer += deltaTime;
    }
    if (this->aiPause) {
        this->aiPauseTimer += deltaTime;
        if (this->aiPauseTimer >= 1500) {
            this->aiPause = false;
            this->aiPauseTimer = 0;
        }
    }
    int currentRow = 2;
    int width = this->screen->getWidth();

    // ANIM
    if (this->hitAnim) {
        if (this->hitAnimTimer < 400) {
//            int originX = this->hitAnimFighterIndex == 0 ? ((width - fighter1->getSprite()->getWidth()) / 5 + rand() % 45)
//                                : ((width - fighter2->getSprite()->getWidth()) * 4 / 5 + rand() % 45);
            this->hitSprite->setColor(this->hitAnimAbilityIndex == 0 ? COLOR_PINK : COLOR_RED);
            this->hitMoveAnim->draw(screen, deltaTime, false);
        } else if (this->hitMoveAnim != nullptr) {
            delete this->hitMoveAnim;
            this->hitMoveAnim = nullptr;
        }
    }

    if (this->hitAnim && this->hitAnimTimer > 1000) {
        this->fighters[this->hitAnimFighterIndex]->takeHit(this->fighters[this->turnIndex]->hit(this->hitAnimAbilityIndex));
        this->hitAnim = false;
        this->turnIndex += 2;
        if (this->turnIndex == 4) {
            this->turnIndex = 1;
        } else if (this->turnIndex == 5) {
            this->turnIndex = 0;
        }
    }

    // HP Bar Tags
    int player1origin = width / 10;
    int player2origin = width * 9 / 10;
    int HPBarWidth = width / 2.8f;
    this->screen->write(this->fighters[0]->getName(), player1origin, currentRow, this->turnIndex == 0 ? COLOR_CYAN : COLOR_WHITE);
    this->screen->write(this->fighters[2]->getName(), player2origin - this->fighters[2]->getName().length(), currentRow,
                        this->turnIndex == 2 ? COLOR_CYAN : COLOR_WHITE);
    this->screen->write(this->fighters[1]->getName(), player1origin, currentRow + 4, this->turnIndex == 1 ? COLOR_CYAN : COLOR_WHITE);
    this->screen->write(this->fighters[3]->getName(), player2origin - this->fighters[2]->getName().length(), currentRow + 4,
                        this->turnIndex == 3 ? COLOR_CYAN : COLOR_WHITE);
    currentRow++;
    // Player 1 Fighter 1
    float currentHP = this->fighters[0]->getCurrentHP();
    float HPratio = currentHP / this->fighters[0]->getMaxHP();
    int currentHPBarWidth = HPBarWidth * HPratio;
    if (currentHPBarWidth == 0 && HPratio > 0) {
        currentHPBarWidth = 1;
    }
    this->screen->horizontalLine(player1origin, currentRow, currentHPBarWidth,
        HPratio > 0.5f ? BG_COLOR_GREEN : (HPratio > 0.25f ? BG_COLOR_YELLOW : BG_COLOR_RED), ' ');
    this->screen->horizontalLine(player1origin, currentRow + 1, currentHPBarWidth,
        HPratio > 0.5f ? BG_COLOR_GREEN : (HPratio > 0.25f ? BG_COLOR_YELLOW : BG_COLOR_RED), ' ');
    // Player 2 Fighter 1
    currentHP = this->fighters[2]->getCurrentHP();
    HPratio = currentHP / this->fighters[2]->getMaxHP();
    currentHPBarWidth = HPBarWidth * HPratio;
    if (currentHPBarWidth == 0 && HPratio > 0) {
        currentHPBarWidth = 1;
    }
    this->screen->horizontalLine(player2origin - (currentHPBarWidth), currentRow, currentHPBarWidth,
        HPratio > 0.5f ? BG_COLOR_GREEN : (HPratio > 0.25f ? BG_COLOR_YELLOW : BG_COLOR_RED), ' ');
    this->screen->horizontalLine(player2origin - (currentHPBarWidth), currentRow + 1, currentHPBarWidth,
        HPratio > 0.5f ? BG_COLOR_GREEN : (HPratio > 0.25f ? BG_COLOR_YELLOW : BG_COLOR_RED), ' ');
    // Player 1 Fighter 2
    currentRow += 4;
    currentHP = this->fighters[1]->getCurrentHP();
    HPratio = currentHP / this->fighters[1]->getMaxHP();
    currentHPBarWidth = HPBarWidth * HPratio;
    if (currentHPBarWidth == 0 && HPratio > 0) {
        currentHPBarWidth = 1;
    }
    this->screen->horizontalLine(player1origin, currentRow, currentHPBarWidth,
        HPratio > 0.5f ? BG_COLOR_GREEN : (HPratio > 0.25f ? BG_COLOR_YELLOW : BG_COLOR_RED), ' ');
    this->screen->horizontalLine(player1origin, currentRow + 1, currentHPBarWidth,
        HPratio > 0.5f ? BG_COLOR_GREEN : (HPratio > 0.25f ? BG_COLOR_YELLOW : BG_COLOR_RED), ' ');
    // Player 2 Fighter 2
    currentHP = this->fighters[3]->getCurrentHP();
    HPratio = currentHP / this->fighters[3]->getMaxHP();
    currentHPBarWidth = HPBarWidth * HPratio;
    if (currentHPBarWidth == 0 && HPratio > 0) {
        currentHPBarWidth = 1;
    }
    this->screen->horizontalLine(player2origin - (currentHPBarWidth), currentRow, currentHPBarWidth,
        HPratio > 0.5f ? BG_COLOR_GREEN : (HPratio > 0.25f ? BG_COLOR_YELLOW : BG_COLOR_RED), ' ');
    this->screen->horizontalLine(player2origin - (currentHPBarWidth), currentRow + 1, currentHPBarWidth,
        HPratio > 0.5f ? BG_COLOR_GREEN : (HPratio > 0.25f ? BG_COLOR_YELLOW : BG_COLOR_RED), ' ');

    // Player Tags
    currentRow = 17;
    // Player1 Fighter 1
    std::string name = this->fighters[0]->getName();
    if ((this->hitAnim && this->hitAnimFighterIndex == 0 && this->hitAnimTimer % 70 < 35) || !this->hitAnim
        || (this->hitAnim && this->hitAnimFighterIndex != 0)) {
        int color = this->fighters[0]->isBlocking() ? COLOR_YELLOW : COLOR_WHITE;
        if (this->turnIndex >= 2 && this->attackIndex == 0) {
            color = COLOR_RED;
        }
        screen->write(name, (width - name.length()) / 5, currentRow, this->turnIndex == 0 ? COLOR_CYAN : color);
    }
    // Player 2 Fighter 1
    name = this->fighters[2]->getName();
    if ((this->hitAnim && this->hitAnimFighterIndex == 2 && this->hitAnimTimer % 70 < 35) || !this->hitAnim
        || (this->hitAnim && this->hitAnimFighterIndex != 2)) {
        int color = this->fighters[2]->isBlocking() ? COLOR_YELLOW : COLOR_WHITE;
        if (this->turnIndex <= 1 && this->attackIndex == 0) {
            color = COLOR_RED;
        }
        screen->write(name, (width - name.length()) * 4 / 5, currentRow, this->turnIndex == 2 ? COLOR_CYAN : color);
    }

    currentRow = 26;

    // Player1 Fighter 2
    name = this->fighters[1]->getName();
    if ((this->hitAnim && this->hitAnimFighterIndex == 1 && this->hitAnimTimer % 70 < 35) || !this->hitAnim
        || (this->hitAnim && this->hitAnimFighterIndex != 1)) {
        int color = this->fighters[1]->isBlocking() ? COLOR_YELLOW : COLOR_WHITE;
        if (this->turnIndex >= 2 && this->attackIndex == 1) {
            color = COLOR_RED;
        }
        screen->write(name, (width - name.length()) / 5, currentRow, this->turnIndex == 1 ? COLOR_CYAN : color);
    }
    // Player 2 Fighter 2
    name = this->fighters[3]->getName();
    if ((this->hitAnim && this->hitAnimFighterIndex == 3 && this->hitAnimTimer % 70 < 35) || !this->hitAnim
        || (this->hitAnim && this->hitAnimFighterIndex != 3)) {
        int color = this->fighters[3]->isBlocking() ? COLOR_YELLOW : COLOR_WHITE;
        if (this->turnIndex <= 1 && this->attackIndex == 1) {
            color = COLOR_RED;
        }
        screen->write(name, (width - name.length()) * 4 / 5, currentRow, this->turnIndex == 3 ? COLOR_CYAN : color);
    }

    // Tooltips
    currentRow += 7;
    // Player 1
    if (this->turnIndex <= 1 && !waitForEnd) {
        int leftmostX = (width - 60) / 5;
        screen->horizontalLine(leftmostX, currentRow, 60, COLOR_BLUE);
        screen->horizontalLine(leftmostX, currentRow + 8, 60, COLOR_BLUE);
        screen->verticalLine(leftmostX, currentRow, 9, COLOR_BLUE);
        screen->verticalLine(leftmostX + 60, currentRow, 9, COLOR_BLUE);
        screen->write("D - " + this->fighters[turnIndex]->getAbility(0)->getName(), leftmostX + 20, currentRow + 2, COLOR_PINK);
        screen->write("S - " + this->fighters[turnIndex]->getAbility(1)->getName(), leftmostX + 20, currentRow + 4, COLOR_RED);
        screen->write("A - Block", leftmostX + 20, currentRow + 6, COLOR_YELLOW);
    }

    // Player 2
    if (this->turnIndex >= 2 && !waitForEnd) {
        int leftmostX = (width - 60) * 4 / 5;
        screen->horizontalLine(leftmostX, currentRow, 60, COLOR_BLUE);
        screen->horizontalLine(leftmostX, currentRow + 8, 60, COLOR_BLUE);
        screen->verticalLine(leftmostX, currentRow, 9, COLOR_BLUE);
        screen->verticalLine(leftmostX + 60, currentRow, 9, COLOR_BLUE);
        screen->write("J - " + this->fighters[turnIndex]->getAbility(0)->getName(), leftmostX + 20, currentRow + 2, COLOR_PINK);
        screen->write("K - " + this->fighters[turnIndex]->getAbility(1)->getName(), leftmostX + 20, currentRow + 4, COLOR_RED);
        screen->write("L - Block", leftmostX + 20, currentRow + 6, COLOR_YELLOW);
    }

    if (!waitForEnd && this->fighters[2]->getCurrentHP() <= 0 && this->fighters[3]->getCurrentHP() <= 0) {
        this->team1->victory();
        Sprite* winner = Database::getWinner();
        this->winAnim = new MoveAnimation(winner, (width - winner->getWidth()) / 4, 30, (width - winner->getWidth()) / 4, 15, 2000);
        Database::getTeam(this->team2->getName())->defeat();
        this->waitForEnd = true;
    } else if (!waitForEnd && this->fighters[0]->getCurrentHP() <= 0 && this->fighters[1]->getCurrentHP() <= 0) {
        this->team1->defeat();
        Database::getTeam(this->team2->getName())->victory();
        Sprite* winner = Database::getWinner();
        this->winAnim = new MoveAnimation(winner, (width - winner->getWidth()) * 3 / 4, 30, (width - winner->getWidth()) * 3 / 4, 15, 2000);
        this->waitForEnd = true;
    }

    if (this->waitForEnd && this->winAnim != nullptr) {
        this->endTimer += deltaTime;
        winAnim->draw(screen, deltaTime, false);
        if (this->endTimer > 2000) {
            delete this->winAnim;
            this->leave = true;
        }
    }

    for (int i = this->turnIndex; !this->waitForEnd && this->fighters[this->turnIndex]->getCurrentHP() <= 0;) {
        if (this->turnIndex % 2 == 0) {
            this->turnIndex++;
        } else {
            this->turnIndex--;
        }
    }

}

void TeamFight::keyInput(int key) {
    if (!this->hitAnim && !this->waitForEnd && !this->aiPause) {
        if ((this->turnIndex % 2 == 0 ? this->team1 : this->team2)->getPlayerType() == PLAYER_TYPE_AI) {
            this->attackIndex = rand() % 2;
            if (this->fighters[this->attackIndex + (this->turnIndex <= 1 ? 2 : 0)]->getCurrentHP() <= 0) {
                this->attackIndex = !this->attackIndex;
            }
        }
        if(this->turnIndex <= 1 && this->team1->getPlayerType() == PLAYER_TYPE_AI) {
            switch (this->fighters[turnIndex]->decide()) {
                case KEY_ABILITY_1:
                    key = KEY_ABILITY_1_PLAYER_1;
                    break;
                case KEY_ABILITY_2:
                    key = KEY_ABILITY_2_PLAYER_1;
                    break;
                case KEY_BLOCK:
                    key = KEY_BLOCK_PLAYER_1;
                    break;
                default:
                    break;
            }
            if (this->team2->getPlayerType() == PLAYER_TYPE_AI) {
                this->aiPause = true;
                this->aiPauseTimer = 0;
            }
        } else if(this->turnIndex >= 2 && this->team2->getPlayerType() == PLAYER_TYPE_AI) {
            switch (this->fighters[turnIndex]->decide()) {
                case KEY_ABILITY_1:
                    key = KEY_ABILITY_1_PLAYER_2;
                    break;
                case KEY_ABILITY_2:
                    key = KEY_ABILITY_2_PLAYER_2;
                    break;
                case KEY_BLOCK:
                    key = KEY_BLOCK_PLAYER_2;
                    break;
                default:
                    break;
            }
            if (this->team1->getPlayerType() == PLAYER_TYPE_AI) {
                this->aiPause = true;
                this->aiPauseTimer = 0;
            }
        }

        bool changeIndex = false;
        switch (key) {
            case KEY_ESC:
                this->leave = true;
                break;
            case KEY_RIGHT:
                break;
            case KEY_LEFT:
                break;
            case KEY_UP:
                this->attackIndex = !this->attackIndex;
                break;
            case KEY_DOWN:
                this->attackIndex = !this->attackIndex;
                break;
            case KEY_BLOCK_PLAYER_1:
                if (this->turnIndex <= 1) {
                    fighters[turnIndex]->block();
                    this->turnIndex += 2;
                    changeIndex = true;
                }
                break;
            case KEY_ABILITY_2_PLAYER_1:
                if (this->turnIndex <= 1) {
                    hit(this->attackIndex + 2, 1);
                }
                break;
            case KEY_ABILITY_1_PLAYER_1:
                if (this->turnIndex <= 1) {
                    hit(this->attackIndex + 2, 0);
                }
                break;
            case KEY_BLOCK_PLAYER_2:
                if (this->turnIndex >= 2) {
                    fighters[turnIndex]->block();
                    this->turnIndex += 2;
                    changeIndex = true;
                }
                break;
            case KEY_ABILITY_2_PLAYER_2:
                if (this->turnIndex >= 2) {
                    hit(this->attackIndex, 1);
                }
                break;
            case KEY_ABILITY_1_PLAYER_2:
                if (this->turnIndex >= 2) {
                    hit(this->attackIndex, 0);
                }
                break;
            default:
                break;
        }
        if (this->turnIndex == 4 && changeIndex) {
            this->turnIndex = 1;
        } else if (this->turnIndex == 5 && changeIndex) {
            this->turnIndex = 0;
        }
    }
}

void TeamFight::hit(int fighterIndex, int abilityIndex) {
    this->hitAnimFighterIndex = fighterIndex;
    this->hitAnimAbilityIndex = abilityIndex;
    this->hitAnim = true;
    this->hitAnimTimer = 0;
    this->hitMoveAnim = new MoveAnimation(this->hitSprite, (this->screen->getWidth() - this->hitSprite->getWidth()) / 2,
                                          this->turnIndex % 2 == 0 ? 13 : 22,
                                          fighterIndex <= 1 ? 0 : this->screen->getWidth() - this->hitSprite->getWidth(),
                                          this->attackIndex == 0 ? 11 : 24, 400);
}
