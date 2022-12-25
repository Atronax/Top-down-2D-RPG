#ifndef ITEM_H
#define ITEM_H

#include "enums.h"
#include "stats.h"

class Item
{    
public:
    Item(ItemType type);
    virtual ~Item();

    const ItemType& getType();
    const QString& getName();
    const QString& skinPath();
    const QString& getDescription();
    const Stats&   getBonus();

    void setType (const ItemType& type);
    void setName (const QString& name);
    void skinPath(const QString& path);
    void setDescription (const QString& description);
    void setBonus (const Stats& bonus);

    bool hasMaster();    

protected:
    virtual void setMaster(Stats* master) = 0;
    virtual void initType(ItemType type) = 0;
    void influence            (bool reverse);

private:
    void influenceOnHPCurrent (bool reverse);
    void influenceOnHPMaximum (bool reverse);
    void influenceOnDamage    (bool reverse);
    void influenceOnDefence   (bool reverse);
    void influenceOnHitchance (bool reverse);
    void influenceOnCritchance(bool reverse);
    void influenceOnSpeed     (bool reverse);
    void influenceOnRange     (bool reverse);

    ItemType type;
    QString name;
    QString imagePath;
    QString description;
    Stats bonus;

    Stats* master;
    Stats overhead;
};

#endif // ITEM_H
