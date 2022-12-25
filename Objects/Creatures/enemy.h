#ifndef ENEMY_H
#define ENEMY_H

#include "creature.h"

class Enemy : public Creature
{
public:
    Enemy(const QRect& rect, const Position& pos, EnemyType type);
    ~Enemy();

    bool isNull();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void turn (Stats& player_stats, Stats& enemy_stats);

private:
    void initEnemy(EnemyType type);
    EnemyType type;

};

#endif // ENEMY_H
