#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "terrain.h"

Terrain::Terrain() : Node()
{
    setZValue(1);
    hidden = false;
    terrainType = TerrainType::None;
    initTerrain(terrainType);
}

Terrain::Terrain(const QRect& rect, TerrainType type) : Node(rect)
{
    setZValue(1);
    hidden = false;
    terrainType = type;
    initTerrain(terrainType);
}

Terrain::~Terrain()
{

}

bool Terrain::isNull()
{
    return (terrainType == TerrainType::None);
}

QString Terrain::toString()
{
    return Node::toString() + " - " + name + " - cost: " + QString::number(cost);
}

int Terrain::getCost()
{
    return cost;
}

void Terrain::setCost(int newCost)
{
    cost = newCost;
}

bool Terrain::isPassable()
{
    return passable;
}

bool Terrain::isHidden()
{
    return hidden;
}

void Terrain::setHidden(bool isHidden)
{
    hidden = isHidden;
}

const TerrainType& Terrain::getTerrainType()
{
    return terrainType;
}

const QString &Terrain::getName()
{
    return name;
}

void Terrain::setTerrainType(const TerrainType &type)
{
    terrainType = type;
    initTerrain(terrainType);
}

void Terrain::initTerrain(TerrainType type)
{
    switch (type)
    {
        case TerrainType::Road:
            fillColorS = QColor(128, 128, 0);
            fillColorT = makeTransparent(fillColorS);
            name = "Road";

            setCost(1);
            passable = true;
            break;

        case TerrainType::Grass:
            skinS = QImage("img\\terrain\\grass.png").scaled(rect().width(), rect().height());
            skinT = makeTransparent(skinS);
            name = "Grass";

            setCost(2);
            passable = true;
            break;

        case TerrainType::Hills:
            fillColorS = QColor(0, 192, 0);
            fillColorT = makeTransparent(fillColorS);
            name = "Hills";

            setCost(5);
            passable = true;
            break;

        case TerrainType::Forest:
            fillColorS = QColor(0, 128, 0);
            fillColorT = makeTransparent(fillColorS);
            name = "Forest";

            setCost(3);
            passable = true;
            break;

        case TerrainType::Mountains:
            fillColorS = QColor(255, 64, 0);
            fillColorT = makeTransparent(fillColorS);
            name = "Mountains";

            setCost(8);
            passable = false;
            break;

        case TerrainType::Sand:        
            fillColorS = QColor(255, 255, 0);
            fillColorT = makeTransparent(fillColorS);
            name = "Sand";

            setCost(5);
            passable = true;
            break;

        case TerrainType::Water:
            fillColorS = QColor(0, 0, 255);
            fillColorT = makeTransparent(fillColorS);
            name = "Water";

            setCost(4);
            passable = false;
            break;

        case TerrainType::None:
            skinS = QImage();
            skinT = QImage();
            fillColorS = QColor(0, 0, 0);
            fillColorT = QColor(0, 0, 0);
            name = "None";

            setCost(9999);
            passable = false;
            break;
    }

    initPainter();
}

void Terrain::initPainter()
{
    int x,y,w,h;
    QRect r = geometry;

    // transparent rectangle
    x = r.x() - mix;
    y = r.y() - mix;
    w = r.width() + mix*2;
    h = r.height() + mix*2;
    transpRect = QRect(x,y,w,h);

    // solid rectangle
    x = r.x() + mix;
    y = r.y() + mix;
    w = r.width() - mix*2;
    h = r.height() - mix*2;
    solidRect = QRect(x,y,w,h);

    // cost rectangle
    x = r.x() + 2 * r.width() / 3;
    y = r.y() + 2 * r.height() / 3;
    w = r.width() / 3;
    h = r.height() / 3;
    costRect = QRect(x,y,w,h);
}

void Terrain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QBrush brushS;
    QBrush brushT;

    if (hidden)
    {
        brushS = QBrush(Qt::black);
        brushT = QBrush(Qt::black);
    }
    else
    {
        if (passable)
        {
            if (!skinS.isNull())
            {
                brushS = QBrush(skinS);
                brushT = QBrush(skinT);
            }
            else
            {
                brushS = QBrush(fillColorS);
                brushT = QBrush(fillColorT);
            }
        }
        else
        {
            if (!skinS.isNull())
            {
                brushS = QBrush(skinS);
                brushT = QBrush(skinT);
            }
            else
            {
                brushS = QBrush(fillColorS, Qt::CrossPattern);
                brushT = QBrush(fillColorT, Qt::CrossPattern);
            }
        }
    }

    painter->setPen(Qt::NoPen);
    painter->fillRect(transpRect, brushT);
    painter->fillRect(solidRect,  brushS);
}

QImage Terrain::makeTransparent(const QImage& solid)
{
    QImage result (solid);

    for (int y = 0; y < solid.height(); ++y)
    {
        for (int x = 0; x < solid.width(); ++x)
        {
            QColor o = solid.pixel(x,y);
            QColor n = QColor(o.red(), o.green(), o.blue(), 128);

            result.setPixelColor(x, y, n);
        }
    }

    return result;
}

QColor Terrain::makeTransparent(const QColor &solid)
{
    QColor result (solid.red(), solid.green(), solid.blue(), 128);

    return result;
}

QDataStream& operator<<(QDataStream &out, const Terrain &from)
{
    out << from.geometry << static_cast<int>(from.terrainType);

    return out;
}

QDataStream& operator>>(QDataStream &in, Terrain &to)
{
    QRect rect;
    int type;

    in >> rect >> type;

    to.geometry = rect;
    to.setTerrainType(static_cast<TerrainType>(type));

    return in;
}
