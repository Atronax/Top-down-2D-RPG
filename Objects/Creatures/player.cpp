#include <QApplication>
#include <QPainter>
#include <QThread>
#include <QDebug>

#include "player.h"
Player::Player(const QRect& r, const Position& p)
    : Creature(r, p)
{
    setSkin(QImage("img\\hero.png"));

    Stats stats;
    stats.setName("Player");
    stats.setType("Player");
    stats.setHPCurrent(10);
    stats.setHPMaximum(10);
    stats.setHitChance(60);
    stats.setCritChance(10);
    stats.setDamage(1, 2);
    stats.setDefence(1);
    stats.setSpeed(2);
    stats.setRange(1);
    setStats(stats);

    busy = false;

    qDebug() << stats.toString();
}

Player::~Player()
{
}

void Player::setGridObjects(GridObjects *o)
{
    objects = o;
}

bool Player::isBusy()
{
    return busy;
}

void Player::keyPressEvent(QKeyEvent *ev)
{
    Node* object = nullptr;
    switch(ev->key())
    {
        case Qt::Key_W:
            if (!isBusy())
            {
                if (canMove(Movement::North) && !objectAt(Movement::North))
                    move (Movement::North);
                else
                    object = objectAt(Movement::North);
            }
            else
                qDebug() << "Player is currently busy";
            break;

        case Qt::Key_D:
            if (!isBusy())
            {
                if (canMove(Movement::East) && !objectAt(Movement::East))
                    move (Movement::East);
                else
                    object = objectAt(Movement::East);
            }
            else
                qDebug() << "Player is currently busy";
            break;

        case Qt::Key_S:
            if (!isBusy())
            {
                if (canMove(Movement::South) && !objectAt(Movement::South))
                    move (Movement::South);
                else
                    object = objectAt(Movement::South);
            }
            else
                qDebug() << "Player is currently busy";
            break;

        case Qt::Key_A:
            if (!isBusy())
            {
                if (canMove(Movement::West) && !objectAt(Movement::West))
                    move (Movement::West);
                else
                    object = objectAt(Movement::West);
            }
            else
                qDebug() << "Player is currently busy";
            break;
    }

    if (object)
    {
        Enemy *enemy = dynamic_cast<Enemy*>(object);
        if (enemy)
            fight(enemy);
    }
}

Node *Player::objectAt(Movement direction)
{
    Position p_position = getPosition();
    Position e_position;
    switch (direction)
    {
        case Movement::North:
            e_position = Position(p_position.x(), p_position.y() - 1);
            break;

        case Movement::East:
            e_position = Position(p_position.x() + 1, p_position.y());
            break;

        case Movement::South:
            e_position = Position(p_position.x(), p_position.y() + 1);
            break;

        case Movement::West:
            e_position = Position(p_position.x() - 1, p_position.y());
            break;
    }

    Enemy *enemy = nullptr;
    if (objects->enemyExists(e_position))
        enemy = objects->enemyAt(e_position);

    return enemy;
}

void Player::fight(Enemy *enemy)
{
    busy = true;

    Stats& p = getStats();
    Stats& e = enemy->getStats();

    bool end = false;
    while (!end)
    {
        // let the creature with greater speed attack first
        if (p.getSpeed() > e.getSpeed())
        {
            turn(p, e);
            enemy->turn(p, e);
        }
        else if (p.getSpeed() == e.getSpeed())
        {
            int current = random(1, 2);
            if (current == 1)
            {
                turn(p, e);
                enemy->turn(p, e);
            }
            else
            {
                enemy->turn(p, e);
                turn(p, e);
            }
        }
        else if (p.getSpeed() < e.getSpeed())
        {
            enemy->turn(p, e);
            turn(p, e);
        }

        // update views of stats
        updateStatsView();
        enemy->updateStatsView();

        // if someone is defeated, make changes and cleanup
        if (e.getHPCurrent() == 0)
        {
            qDebug() << "enemy DIED";
            // do smth with ui
            // do smth with enemy
            objects->removeEnemy(enemy);
            end = true;
        }        

        if (p.getHPCurrent() == 0)
        {
            qDebug() << "player DIED";
            // do smth with ui
            // do smth with player
            // do smth with game (reload\exit)
            end = true;
        }
    }

    busy = false;
}

void Player::turn(Stats& player_stats, Stats& enemy_stats)
{
    if (player_stats.getHPCurrent() > 0 && enemy_stats.getHPCurrent() > 0)
    {
        int p_hit = random(1, 100);
        int p_crit = random(1, 100);
        if (player_stats.getHitChance() > p_hit)
        {
            int damage = abs(enemy_stats.getDefence() - random(player_stats.getDamage().x(), player_stats.getDamage().y()));
            if (player_stats.getCritChance() > p_crit)
            {
                damage *= 2;
                qDebug() << "PLAYER HITS WITH CRITICAL STRIKE: " + QString::number(damage);
            }

            enemy_stats.setHPCurrent(enemy_stats.getHPCurrent() - damage);

            qDebug() << "PLAYER HITS: " << damage << ", enemy HP - " << enemy_stats.getHPCurrent() << "/" << enemy_stats.getHPMaximum();
            if (enemy_stats.getHPCurrent() <= 0)
                enemy_stats.setHPCurrent(0);
        }
        else
            qDebug() << "PLAYER MISSED: " << p_hit << "\\" << player_stats.getHitChance();                       

        // delay between turns
        qApp->processEvents();
        QThread::msleep(100);
    }

}
