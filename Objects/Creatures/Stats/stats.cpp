#include <QDebug>
#include "stats.h"

Stats::Stats()
{

}

Stats::~Stats()
{

}

QString Stats::toString()
{
    QString str_creature = "Creature " + name + ": ";
    QString str_hp = "HP" + QString::number(hp_current) + ", ";
    QString str_hitchance = "HIT" + QString::number(hitchance) + ", ";
    QString str_critchance = "CRIT" + QString::number(critchance) + ", ";
    QString str_damage = "DMG" + QString::number(damage.x()) + "-" + QString::number(damage.y()) +", ";
    QString str_defence = "DFS" + QString::number(defence) + ", ";
    QString str_speed = "SPD" + QString::number(speed) + ", ";
    QString str_range = "RNG" + QString::number(range);

    return str_creature + str_hp + str_hitchance + str_critchance + str_damage + str_defence + str_speed + str_range;
}

const QString &Stats::getName()
{
    return name;
}

const QString &Stats::getType()
{
    return type;
}

int Stats::getHPCurrent()
{
    return hp_current;
}

int Stats::getHPMaximum()
{
    return hp_maximum;
}

int Stats::getHitChance()
{
    return hitchance;
}

int Stats::getCritChance()
{
    return critchance;
}

QPoint Stats::getDamage()
{
    return damage;
}

int Stats::getDefence()
{
    return defence;
}

int Stats::getSpeed()
{
    return speed;
}

int Stats::getRange()
{
    return range;
}

void Stats::setName(const QString &value)
{
    name = value;
}

void Stats::setType(const QString &value)
{
    type = value;
}

void Stats::setHPCurrent(int value)
{
    hp_current = value;
}

void Stats::setHPMaximum(int value)
{
    if (value > 0)
        hp_maximum = value;
    else
        qDebug() << "Wrong STATS (setHPMaximum): check if value > 0";
}

void Stats::setHitChance(int value)
{
    if (value > 0 && value < MAX_hitchance)
        hitchance = value;
    else
        qDebug() << "Wrong STATS (setHitChance): check if value > 0 && value < MAX_hitchance";
}

void Stats::setCritChance(int value)
{
    if (value > 0 && value < MAX_critchance)
        critchance = value;
    else
        qDebug() << "Wrong STATS (setCritChance): check if value > 0 && value < MAX_critchance";
}

void Stats::setDamage(int value_low, int value_high)
{
    if (value_low >= 0 && value_high > value_low)
    {
        damage.setX(value_low);
        damage.setY(value_high);
    }
    else
        qDebug() << "Wrong STATS (setDamage): check if value_low >= 0 && value_high > value_low";
}

void Stats::setDefence(int value)
{
    if (value >= 0)
        defence = value;
    else
        qDebug() << "Wrong STATS (setDefence): check if value >= 0";
}

void Stats::setSpeed(int value)
{
    if (value >= 0)
        speed = value;
    else
        qDebug() << "Wrong STATS (setSpeed): check if value >= 0";
}

void Stats::setRange(int value)
{
    if (value > 0)
        range = value;
    else
        qDebug() << "Wrong STATS (setRange): check if value > 0";
}

int Stats::getMAX_hitchance()
{
    return MAX_hitchance;
}

int Stats::getMAX_critchance()
{
    return MAX_critchance;
}

int Stats::getMAX_range()
{
    return MAX_range;
}

Stats &Stats::operator=(const Stats &rhs)
{
    name = rhs.name;
    type = rhs.type;
    hp_current = rhs.hp_current;
    hp_maximum = rhs.hp_maximum;
    hitchance = rhs.hitchance;
    critchance = rhs.critchance;
    damage = rhs.damage;
    defence = rhs.defence;
    speed = rhs.speed;
    range = rhs.range;

    return *this;
}
