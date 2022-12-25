#include "item.h"

Item::Item(ItemType t)
{
    type = t;
}

Item::~Item()
{

}

const ItemType &Item::getType()
{
    return type;
}

const QString &Item::getName()
{
    return name;
}

const QString &Item::getDescription()
{
    return description;
}

void Item::setType(const ItemType &t)
{
    type = t;
}

const QString &Item::skinPath()
{
    return imagePath;
}

void Item::setName(const QString &n)
{
    name = n;
}

void Item::setDescription(const QString &d)
{
    description = d;
}

void Item::skinPath(const QString &p)
{
    imagePath = p;
}

bool Item::hasMaster()
{
    return (master != nullptr);
}

void Item::setMaster(Stats *m)
{
    master = m;
}

void Item::influence(bool reverse)
{
    // TO DO:
    // 1. ex.: +30% attack power
    // 2. ex.: -hp max, +defence
    influenceOnHPCurrent(reverse);
    influenceOnHPMaximum(reverse);
    influenceOnDamage(reverse);
    influenceOnDefence(reverse);
    influenceOnHitchance(reverse);
    influenceOnCritchance(reverse);
    influenceOnSpeed(reverse);
    influenceOnRange(reverse);
}

void Item::influenceOnHPCurrent(bool reverse)
{
    if (bonus.getHPCurrent() > 0)
    {
        if (!reverse)
        {
            master->setHPCurrent(master->getHPCurrent() + bonus.getHPCurrent());
            if (master->getHPCurrent() > master->getHPMaximum())
            {
                overhead.setHPCurrent(master->getHPCurrent() - master->getHPMaximum());
                master->setHPCurrent(master->getHPMaximum());
            }
        }
        else
        {
            master->setHPCurrent(master->getHPCurrent() - bonus.getHPCurrent());
            if (overhead.getHPCurrent() > 0)
                master->setHPCurrent(master->getHPCurrent() + overhead.getHPCurrent());
        }
    }
}

void Item::influenceOnHPMaximum(bool reverse)
{
    if (bonus.getHPMaximum() > 0)
    {
        if (!reverse)
        {
            master->setHPMaximum(master->getHPMaximum() + bonus.getHPMaximum());
            master->setHPCurrent(master->getHPCurrent() + bonus.getHPMaximum());
        }
        else
        {
            master->setHPMaximum(master->getHPMaximum() - bonus.getHPMaximum());

            int HPLeft = master->getHPCurrent() - bonus.getHPMaximum();
            if (HPLeft < 1)
                master->setHPCurrent(1);
            else
                master->setHPCurrent(HPLeft);
        }
    }
}

void Item::influenceOnDamage(bool reverse)
{
    if (bonus.getDamage().x() > 0 && bonus.getDamage().y() > 0)
    {
        if (!reverse)
        {
            master->setDamage(master->getDamage().x() + bonus.getDamage().x(), master->getDamage().y() + bonus.getDamage().y());
        }
        else
        {
            master->setDamage(master->getDamage().x() - bonus.getDamage().x(), master->getDamage().y() - bonus.getDamage().y());
        }
    }
}

void Item::influenceOnDefence(bool reverse)
{
    if (bonus.getDefence() > 0)
    {
        if (!reverse)
        {
            master->setDefence(master->getDefence() + bonus.getDefence());
        }
        else
        {
            master->setDefence(master->getDefence() - bonus.getDefence());
        }
    }
}

void Item::influenceOnHitchance(bool reverse)
{
    if (bonus.getHitChance() > 0)
    {
        if (!reverse)
        {
            master->setHitChance(master->getHitChance() + bonus.getHitChance());
            if (master->getHitChance() > master->getMAX_hitchance())
            {
                overhead.setHitChance(master->getHitChance() - master->getMAX_hitchance());
                master->setHitChance(master->getMAX_hitchance());
            }
        }
        else
        {
            master->setHitChance(master->getHitChance() - bonus.getHitChance());
            if (overhead.getHitChance() > 0)
                master->setHitChance(master->getHitChance() + overhead.getHitChance());
        }
    }
}

void Item::influenceOnCritchance(bool reverse)
{
    if (bonus.getCritChance() > 0)
    {
        if (!reverse)
        {
            master->setCritChance(master->getCritChance() + bonus.getCritChance());
            if (master->getCritChance() > master->getMAX_critchance())
            {
                overhead.setCritChance(master->getCritChance() - master->getMAX_critchance());
                master->setCritChance(master->getMAX_critchance());
            }
        }
        else
        {
            master->setCritChance(master->getCritChance() - bonus.getCritChance());
            if (overhead.getCritChance() > 0)
                master->setCritChance(master->getCritChance() + overhead.getCritChance());
        }
    }
}

void Item::influenceOnSpeed(bool reverse)
{
    if (bonus.getSpeed() > 0)
    {
        if (!reverse)
        {
            master->setSpeed(master->getSpeed() + bonus.getSpeed());
        }
        else
        {
            master->setSpeed(master->getSpeed() - bonus.getSpeed());
        }
    }
}

void Item::influenceOnRange(bool reverse)
{
    if (bonus.getRange() > 0)
    {
        if (!reverse)
        {
            master->setRange(master->getRange() + bonus.getRange());
            if (master->getRange() > master->getMAX_range())
            {
                overhead.setRange(master->getRange() - master->getMAX_range());
                master->setRange(master->getMAX_range());
            }
        }
        else
        {
            master->setRange(master->getRange() - bonus.getRange());
            if (overhead.getRange() > 0)
                master->setRange(master->getRange() + overhead.getRange());
        }
    }
}
