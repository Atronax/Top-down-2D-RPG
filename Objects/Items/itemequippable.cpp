#include "itemequippable.h"

ItemEquippable::ItemEquippable(ItemType type) : Item (type)
{
    initType(type);
}

ItemEquippable::~ItemEquippable()
{

}

void ItemEquippable::equip()
{
    if (hasMaster() && !isEquipped())
    {
        influence (false);
        equipped = true;
    }
}

void ItemEquippable::unequip()
{
    if (hasMaster() && isEquipped())
    {
        influence (true);
        equipped = false;
    }
}

bool ItemEquippable::isEquipped()
{
    return equipped;
}


void ItemEquippable::setMaster(Stats *m)
{
    if (m)
    {
        if (isEquipped())
        {
            unequip();
            equip();
        }

        Item::setMaster(m);
    }
}

void ItemEquippable::initType(ItemType type)
{
    switch (type)
    {
        case ItemType::Head:
        break;

        case ItemType::Shoulders:
        break;

        case ItemType::Torso:
        break;

        case ItemType::Waist:
        break;

        case ItemType::Leggings:
        break;

        case ItemType::Boots:
        break;

        case ItemType::Amulet:
        break;

        case ItemType::Ring:
        break;

        case ItemType::Gloves:
        break;

        default:
        break;
    }
}
