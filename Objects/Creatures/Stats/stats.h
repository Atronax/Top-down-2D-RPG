#ifndef STATS_H
#define STATS_H

#include <QString>
#include <QPoint>

class Stats
{
public:
    Stats();
    ~Stats();

    QString toString();

    const QString& getName();
    const QString& getType();
    int getHPCurrent();
    int getHPMaximum();
    int getHitChance();
    int getCritChance();
    QPoint getDamage();
    int getDefence();
    int getSpeed();
    int getRange();

    void setName(const QString& value);
    void setType(const QString& value);
    void setHPCurrent(int value);
    void setHPMaximum(int value);
    void setHitChance(int value);
    void setCritChance(int value);
    void setDamage(int value_low, int value_high);
    void setDefence(int value);
    void setSpeed(int value);
    void setRange(int value);

    int getMAX_hitchance();
    int getMAX_critchance();
    int getMAX_range();

    Stats& operator= (const Stats& rhs);

private:
    QString name;
    QString type;
    int hp_current;
    int hp_maximum;
    int hitchance;
    int critchance;
    QPoint damage;
    int defence;
    int speed;
    int range;

    // maximum values
    const int MAX_hitchance = 95;
    const int MAX_critchance = 45;
    const int MAX_range = 10;
};

#endif // STATS_H
