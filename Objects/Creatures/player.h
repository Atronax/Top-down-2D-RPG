#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include "creature.h"
#include "gridobjects.h"

class Player : public Creature
{
public:
    Player(const QRect& rect, const Position& pos);
    ~Player();    

    void keyPressEvent(QKeyEvent* ev);

    void setGridObjects(GridObjects* objects);

    bool isBusy();

    void fight(Enemy* enemy);
    void turn(Stats& player_stats, Stats& enemy_stats);

private:
    Node* objectAt(Movement direction);
    GridObjects *objects;

    bool busy;
};

#endif // PLAYER_H
