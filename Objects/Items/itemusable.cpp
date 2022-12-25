#include "itemusable.h"

ItemUsable::ItemUsable(ItemType type) : Item(type)
{    
    initType(type);
}

ItemUsable::~ItemUsable()
{

}

ItemUsableLogic *ItemUsable::logic()
{
    return pLogic;
}

void ItemUsable::use()
{
    if (hasMaster() && !hasStarted())
    {
        influence (false);
        started = true;
    }
}

void ItemUsable::rev()
{
    if (hasMaster() && hasStarted() && !hasFinished())
    {
        influence (true);
        finished = true;
    }
}

bool ItemUsable::hasStarted()
{
    return started;
}

bool ItemUsable::hasFinished()
{
    return finished;
}

bool ItemUsable::isPermanent()
{
    return permanent;
}

bool ItemUsable::isTemporary()
{
    return temporary;
}

bool ItemUsable::isPeriodic()
{
    return periodic;
}

int ItemUsable::getDuration()
{
    return duration;
}

int ItemUsable::getPeriods()
{
    return periods;
}

void ItemUsable::setDuration(int time)
{
    if (time > 0)
    {
        duration = time;
        temporary = true;
    }
}

void ItemUsable::setPeriods(int count)
{
    periods = count;
}

// PROTECTED ZONE
void ItemUsable::setMaster(Stats *m)
{
    if (m)
    {
        if (hasStarted() && !hasFinished())
            rev();

        Item::setMaster(m);
    }
}

void ItemUsable::initType(ItemType type)
{
    pLogic = new ItemUsableLogic(this);
    started = false;
    finished = false;
    permanent = false;
    temporary = false;
    periodic = false;

    switch (type)
    {
        case ItemType::Potion_Permanent:
        permanent = true;
        break;

        case ItemType::Potion_Temporary:
        temporary = true;
        break;

        case ItemType::Potion_Periodic:
        periodic = true;
        break;

        default:
        break;
    }
}

// ItemUsableLogic functionality
ItemUsableLogic::ItemUsableLogic(ItemUsable *i)
{
    item = i;
}

ItemUsableLogic::~ItemUsableLogic()
{
    timer->deleteLater();
}

void ItemUsableLogic::use()
{
    if (item->isTemporary())
        useTemporary();
    else if (item->isPeriodic())
        usePeriodic();
    else if (item->isPermanent())
        usePermanent();
}

void ItemUsableLogic::usePermanent()
{
    item->use();
}

void ItemUsableLogic::usePeriodic()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(onPeriodic()));

    item->use();
    timer->start(item->getDuration());
}

void ItemUsableLogic::useTemporary()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(onTemporary()));

    item->use();
    timer->setSingleShot(true);
    timer->start(item->getDuration());
}


void ItemUsableLogic::onTemporary()
{
    item->rev();

    disconnect(timer, SIGNAL(timeout()), this, SLOT(onTemporary()));
}

void ItemUsableLogic::onPeriodic()
{
    item->use();

    item->setPeriods(item->getPeriods() - 1);
    if (item->getPeriods() == 0)
        disconnect(timer, SIGNAL(timeout()), this, SLOT(onPeriodic()));
}
