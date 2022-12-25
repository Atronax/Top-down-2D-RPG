#ifndef ENUMS_H
#define ENUMS_H

enum class TerrainType
{
    Road = 0,
    Grass = 1,
    Hills = 2,
    Forest = 3,
    Mountains = 4,
    Sand = 5,
    Water = 6,
    None = 100
};

enum class EnemyType
{
    Spider = 0,
    None = 100
};

enum class ItemType
{
    Head = 0,
    Shoulders = 1,
    Torso = 2,
    Leggings = 3,
    Boots = 4,
    Gloves = 5,
    Waist = 6,
    Amulet = 7,
    Ring = 8,
    Potion_Permanent = 20,
    Potion_Temporary = 21,
    Potion_Periodic = 22,
};

enum class Movement
{
    North = 0,
    East = 1,
    South = 2,
    West = 3
};

#endif // ENUMS_H
