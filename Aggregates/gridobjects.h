#ifndef GRIDOBJECTS_H
#define GRIDOBJECTS_H

#include <QMap>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "position.h"
#include "enemy.h"

class GridObjects
{
public:
    GridObjects(QGraphicsScene* scene, QGraphicsView* view);
    ~GridObjects();

    Enemy* makeEnemy(const QRect& rectangle, const Position& position, EnemyType type);
    void addEnemy(const Position& position, Enemy* enemy);
    void replaceEnemy(Enemy* oldEnemy, Enemy* newEnemy);
    void removeEnemy(Enemy* enemy);

    bool   enemyExists(const Position& position);
    Enemy* enemyAt(const Position& position);

private:
    void clear(const QString& what);

    QGraphicsScene* scene;
    QGraphicsView* view;
    QMap<Position, Enemy*> *enemies;
};

#endif // GRIDOBJECTS_H
