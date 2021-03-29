#include "../headers/fightclub.h"

Fight::Fight(Screen* screen, Fighter* fighter1, Fighter* fighter2) : GameState(screen) {
    this->fighter1 = fighter1;
    if (fighter1->getName().compare(fighter2->getName()) == 0) {
        this->fighter2 = fighter2->clone();
        this->fighter2Copy = true;
    } else {
        this->fighter2 = fighter2;
    }
    this->turnIndex = rand() % 2;
    this->hitSprite = Database::getHitSprite();
}

Fight::~Fight() {
    fighter1->heal();
    fighter1->getSprite()->setColor(COLOR_WHITE);
    fighter2->heal();
    fighter2->getSprite()->setColor(COLOR_WHITE);
    if (this->fighter2Copy) {
        delete this->fighter2;
    }
}

void Fight::update(int deltaTime) {
    if (this->hitAnim) {
        hitAnimTimer += deltaTime;
    }
    int currentRow = 2;
    int width = this->screen->getWidth();

    // ANIM
    if (this->hitAnim) {
        if (this->hitAnimTimer < 400) {
            int originX = this->hitAnimFighterIndex == 0 ? ((width - fighter1->getSprite()->getWidth()) / 5 + rand() % 45)
                                : ((width - fighter2->getSprite()->getWidth()) * 4 / 5 + rand() % 45);
            this->hitSprite->setColor(this->hitAnimAbilityIndex == 0 ? COLOR_PINK : COLOR_RED);
            this->hitMoveAnim->draw(screen, deltaTime, false);
        } else if (this->hitMoveAnim != nullptr) {
            delete this->hitMoveAnim;
            this->hitMoveAnim = nullptr;
        }
    }

    if (this->hitAnim && this->hitAnimTimer > 1000) {
        (this->hitAnimFighterIndex == 0 ? this->fighter1 : this->fighter2)->takeHit((this->hitAnimFighterIndex == 0 ? this->fighter2
                                                        : this->fighter1)->hit(this->hitAnimAbilityIndex));
        this->hitAnim = false;
        this->turnIndex = this->turnIndex == 0 ? 1 : 0;
    }

    // HP Bars
    int player1origin = width / 10;
    int player2origin = width * 9 / 10;
    int HPBarWidth = width / 2.8f;
    this->screen->write(this->fighter1->getName(), player1origin, currentRow);
    this->screen->write(this->fighter2->getName(), player2origin - this->fighter2->getName().length(), currentRow);
    currentRow++;
    // Player 1
    float currentHP = this->fighter1->getCurrentHP();
    float HPratio = currentHP / this->fighter1->getMaxHP();
    int currentHPBarWidth = HPBarWidth * HPratio;
    if (currentHPBarWidth == 0 && HPratio > 0) {
        currentHPBarWidth = 1;
    }
    this->screen->horizontalLine(player1origin, currentRow, currentHPBarWidth,
        HPratio > 0.5f ? BG_COLOR_GREEN : (HPratio > 0.25f ? BG_COLOR_YELLOW : BG_COLOR_RED), ' ');
    this->screen->horizontalLine(player1origin, currentRow + 1, currentHPBarWidth,
        HPratio > 0.5f ? BG_COLOR_GREEN : (HPratio > 0.25f ? BG_COLOR_YELLOW : BG_COLOR_RED), ' ');
    // Player 2
    currentHP = this->fighter2->getCurrentHP();
    HPratio = currentHP / this->fighter2->getMaxHP();
    currentHPBarWidth = HPBarWidth * HPratio;
    if (currentHPBarWidth == 0 && HPratio > 0) {
        currentHPBarWidth = 1;
    }
    this->screen->horizontalLine(player2origin - (currentHPBarWidth), currentRow, currentHPBarWidth,
        HPratio > 0.5f ? BG_COLOR_GREEN : (HPratio > 0.25f ? BG_COLOR_YELLOW : BG_COLOR_RED), ' ');
    this->screen->horizontalLine(player2origin - (currentHPBarWidth), currentRow + 1, currentHPBarWidth,
        HPratio > 0.5f ? BG_COLOR_GREEN : (HPratio > 0.25f ? BG_COLOR_YELLOW : BG_COLOR_RED), ' ');

    // PICS
    currentRow = 7;
    // Player1
    Sprite* sprite = this->fighter1->getSprite();
    if ((this->hitAnim && this->hitAnimFighterIndex == 0 && this->hitAnimTimer % 70 < 35) || !this->hitAnim
        || (this->hitAnim && this->hitAnimFighterIndex == 1)) {
        sprite->draw(screen, (width - sprite->getWidth()) / 5, currentRow);
    }
    // Player 2
    sprite = this->fighter2->getSprite();
    if ((this->hitAnim && this->hitAnimFighterIndex == 1 && this->hitAnimTimer % 70 < 35) || !this->hitAnim
        || (this->hitAnim && this->hitAnimFighterIndex == 0)) {
        sprite->draw(screen, (width - sprite->getWidth()) * 4 / 5, currentRow, true);
    }

    // Tooltips
    currentRow += 30;
    // Player 1
    if (this->turnIndex == 0 && !waitForEnd) {
        int leftmostX = (width - 60) / 5;
        screen->horizontalLine(leftmostX, currentRow, 60, COLOR_BLUE);
        screen->horizontalLine(leftmostX, currentRow + 8, 60, COLOR_BLUE);
        screen->verticalLine(leftmostX, currentRow, 9, COLOR_BLUE);
        screen->verticalLine(leftmostX + 60, currentRow, 9, COLOR_BLUE);
        screen->write("D - " + this->fighter1->getAbility(0)->getName(), leftmostX + 20, currentRow + 2, COLOR_PINK);
        screen->write("S - " + this->fighter1->getAbility(1)->getName(), leftmostX + 20, currentRow + 4, COLOR_RED);
        screen->write("A - Block", leftmostX + 20, currentRow + 6, COLOR_YELLOW);
    }

    if (this->turnIndex == 1 && !waitForEnd) {
        int leftmostX = (width - 60) * 4 / 5;
        screen->horizontalLine(leftmostX, currentRow, 60, COLOR_BLUE);
        screen->horizontalLine(leftmostX, currentRow + 8, 60, COLOR_BLUE);
        screen->verticalLine(leftmostX, currentRow, 9, COLOR_BLUE);
        screen->verticalLine(leftmostX + 60, currentRow, 9, COLOR_BLUE);
        screen->write("J - " + this->fighter2->getAbility(0)->getName(), leftmostX + 20, currentRow + 2, COLOR_PINK);
        screen->write("K - " + this->fighter2->getAbility(1)->getName(), leftmostX + 20, currentRow + 4, COLOR_RED);
        screen->write("L - Block", leftmostX + 20, currentRow + 6, COLOR_YELLOW);
    }

    if (!waitForEnd && this->fighter2->getCurrentHP() <= 0) {
        this->fighter1->victory();
        Sprite* winner = Database::getWinner();
        this->winAnim = new MoveAnimation(winner, (width - winner->getWidth()) / 4, 30, (width - winner->getWidth()) / 4, 15, 2000);
        Database::getFighter(this->fighter2->getName())->defeat();
        this->waitForEnd = true;
    } else if (!waitForEnd && this->fighter1->getCurrentHP() <= 0) {
        this->fighter1->defeat();
        Database::getFighter(this->fighter2->getName())->victory();
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
}

void Fight::keyInput(int key) {
    if (!hitAnim && !waitForEnd) {
        switch (key) {
            case KEY_ESC:
                this->leave = true;
                break;
            case KEY_RIGHT:
                break;
            case KEY_LEFT:
                break;
            case 'A':
                if (this->turnIndex == 0) {
                    fighter1->block();
                    this->turnIndex = 1;
                }
                break;
            case 'S':
                if (this->turnIndex == 0) {
                    hit(1, 1);
                }
                break;
            case 'D':
                if (this->turnIndex == 0) {
                    hit(1, 0);
                }
                break;
            case 'L':
                if (this->turnIndex == 1) {
                    fighter2->block();
                    this->turnIndex = 0;
                }
                break;
            case 'K':
                if (this->turnIndex == 1) {
                    hit(0, 1);
                }
                break;
            case 'J':
                if (this->turnIndex == 1) {
                    hit(0, 0);
                }
                break;
            default:
                break;
        }
    }
}

void Fight::hit(int fighterIndex, int abilityIndex) {
    this->hitAnim = true;
    this->hitAnimFighterIndex = fighterIndex;
    this->hitAnimAbilityIndex = abilityIndex;
    this->hitAnim = true;
    this->hitAnimTimer = 0;
    this->hitMoveAnim = new MoveAnimation(this->hitSprite, (this->screen->getWidth() - this->hitSprite->getWidth()) / 2, 15,
                                          fighterIndex == 0 ? 0 : this->screen->getWidth() - this->hitSprite->getWidth(), 25, 400);
}
