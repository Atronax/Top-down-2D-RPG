#include <QDebug>

#include "gridobjects.h"

GridObjects::GridObjects(QGraphicsScene *s, QGraphicsView *v)
{
   scene = s;
   view = v;
   enemies = new QMap<Position, Enemy*>();
}

GridObjects::~GridObjects()
{
    clear("enemies");
}

Enemy *GridObjects::makeEnemy(const QRect &rectangle, const Position& position, EnemyType type)
{
    Enemy* e = new Enemy(rectangle, position, type);
    addEnemy(position, e);

    return e;
}

void GridObjects::clear(const QString& what)
{
    if (what == "enemies")
    {
        if (enemies && !enemies->isEmpty())
        {
            int count = enemies->size();
            for (int i = 0; i < count; ++i)
            {
                Enemy* enemy = enemies->values().at(i);
                scene->removeItem(enemy);
                delete enemy;
            }

            enemies->clear();
            delete enemies;
        }
    }
}

void GridObjects::addEnemy(const Position &position, Enemy *enemy)
{
    if (enemies->contains(position))
    {
        replaceEnemy(enemies->value(position), enemy);
    }
    else
    {
        enemies->insert(position, enemy);
        scene->addItem(enemy);
    }
}

void GridObjects::replaceEnemy(Enemy *oldEnemy, Enemy *newEnemy)
{
    Position key = enemies->key(oldEnemy);

    enemies->remove(key);
    enemies->insert(key, newEnemy);

    scene->removeItem(oldEnemy);
    scene->addItem(newEnemy);

    delete oldEnemy;
}

void GridObjects::removeEnemy(Enemy *enemy)
{
    Position key = enemies->key(enemy);

    enemies->remove(key);
    scene->removeItem(enemy);

    delete enemy;
}

bool GridObjects::enemyExists(const Position &position)
{
    return enemies->contains(position);
}

Enemy *GridObjects::enemyAt(const Position &position)
{
    return enemies->value(position);
}
