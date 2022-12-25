#ifndef TERRAIN_H
#define TERRAIN_H

#include "enums.h"
#include "node.h"
class Terrain : public Node
{
public:
    Terrain();
    Terrain(const QRect& rect, TerrainType type);
    ~Terrain();

    bool isNull();
    bool isHidden();
    bool isPassable();
    QString toString();

    const TerrainType& getTerrainType();
    const QString& getName();
    int getCost();

    void setTerrainType (const TerrainType& type);
    void setHidden (bool isHidden);
    void setCost(int newCost);

    friend QDataStream& operator<< (QDataStream&, const Terrain&);
    friend QDataStream& operator>> (QDataStream&, Terrain&);

    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    QImage makeTransparent (const QImage& solid);
    QColor makeTransparent (const QColor& solid);

    void initTerrain (TerrainType type);
    void initPainter ();

    QImage skinS, skinT;
    QColor fillColorS, fillColorT;

    QRect transpRect;
    QRect solidRect;
    QRect costRect;
    const int mix = 2; // pixels we get as mix of several terrains

    TerrainType terrainType;
    QString name;
    bool passable;
    bool hidden;
    int cost;

};

#endif // TERRAIN_H
