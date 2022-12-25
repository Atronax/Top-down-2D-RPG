#include <QApplication>
#include <QThread>
#include <QDebug>

#include "enemy.h"

Enemy::Enemy(const QRect &r, const Position &p, EnemyType t)
    : Creature(r, p)
{
    type = t;
    initEnemy(type);
}

Enemy::~Enemy()
{

}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Creature::paint(painter, option, widget);
}

bool Enemy::isNull()
{
    return (type == EnemyType::None);
}

void Enemy::initEnemy(EnemyType type)
{
    Stats stats;
    stats.setType("Enemy");

    switch (type)
    {
        case EnemyType::Spider:
            setSkin(QImage("img\\creatures\\enemies\\spider.png"));
            stats.setName("Spider");
            stats.setHPCurrent(5);
            stats.setHPMaximum(5);
            stats.setHitChance(40);
            stats.setCritChance(15);
            stats.setDamage(2, 2);
            stats.setDefence(0);
            stats.setSpeed(2);
            stats.setRange(2);
            break;

        case EnemyType::None:
            break;
    }

    setStats(stats);
}

void Enemy::turn(Stats &player_stats, Stats &enemy_stats)
{
    if (enemy_stats.getHPCurrent() > 0 && player_stats.getHPCurrent() > 0)
    {
        int e_hit = random(1, 100);
        int e_crit = random(1, 100);
        if (enemy_stats.getHitChance() > e_hit)
        {
            int damage = abs(player_stats.getDefence() - random(enemy_stats.getDamage().x(), enemy_stats.getDamage().y()));
            if (enemy_stats.getCritChance() > e_crit)
            {
                damage *= 2;
                qDebug() << "ENEMY HITS WITH CRITICAL STRIKE: " + QString::number(damage);
            }

            player_stats.setHPCurrent(player_stats.getHPCurrent() - damage);            

            qDebug() << "ENEMY HITS: " << damage << ", player HP - " << player_stats.getHPCurrent() << "/" << player_stats.getHPMaximum();
            if (player_stats.getHPCurrent() <= 0)
                player_stats.setHPCurrent(0);
        }
        else
            qDebug() << "ENEMY MISSED: " << e_hit << "\\" << enemy_stats.getHitChance();

        // delay between turns
        qApp->processEvents();
        QThread::msleep(100);
    }
}

