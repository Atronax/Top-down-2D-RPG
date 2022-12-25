#ifndef ITEMEQUIPPABLE_H
#define ITEMEQUIPPABLE_H

#include "item.h"

class ItemEquippable : public Item
{
public:
    ItemEquippable(ItemType type);
    ~ItemEquippable();

    void equip();
    void unequip();

    bool isEquipped();    

protected:
    void setMaster(Stats* master);
    void initType(ItemType type);

private:
    bool equipped;
};

#endif // ITEMEQUIPPABLE_H
