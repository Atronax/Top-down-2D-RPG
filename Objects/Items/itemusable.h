#ifndef ITEMUSABLE_H
#define ITEMUSABLE_H

#include <QObject>
#include <QTimer>

#include "item.h"

// If we want to serialize 'ItemUsable' class, it must be simple data type. At the same time we want to implement logic
// based on QTimer, which needs container to be a QObject and have Q_OBJECT macro. As we know from Qt documentation,
// classes with Q_OBJECT macro can not be serialized using QDataStream. So we separate 'ItemUsable' into two classes.
// 'ItemUsable' class will create the 'ItemUsableLogic' part, hold its pointer and use it whenever needed.

class ItemUsableLogic;

class ItemUsable : public Item
{
    friend class ItemUsableLogic;

public:
    ItemUsable(ItemType type);
    ~ItemUsable();

    ItemUsableLogic* logic();

    bool isPermanent();
    bool isTemporary();
    bool isPeriodic();

    int  getDuration();
    int  getPeriods();

    void setDuration(int time);
    void setPeriods(int count);    

    bool hasStarted();
    bool hasFinished();

protected:
    void setMaster(Stats *master);
    void initType(ItemType type);

private:
    void use();
    void rev();

    bool permanent;
    bool temporary;
    bool periodic;

    int  duration;
    int  periods;

    bool started;
    bool finished;

    ItemUsableLogic* pLogic;
};

class ItemUsableLogic : public QObject
{
    Q_OBJECT

public:
    ItemUsableLogic(ItemUsable* item);
    ~ItemUsableLogic();

    void use();

private:
    void usePermanent(); // 1. Single shot usables - permanent stats ( +2 defence forever)
    void usePeriodic();  // 2. Periodic shot usables - periodic stats ( +10 hp / sec for each second for 3 sec)
    void useTemporary(); // 3. Fixed time usables - temporary stats ( +5 damage for 30 sec)

    ItemUsable* item;
    QTimer* timer;

public slots:
    void onTemporary();
    void onPeriodic();
};

#endif // ITEMUSABLE_H
