#include <QDebug>
#include <QScrollBar>

#include "grid.h"

Grid::Grid(QGraphicsScene *s, QGraphicsView *v)
{
    scene = s;
    view = v;
    map = new QMap<Position, Terrain*>();
}

Grid::~Grid()
{
    clear();
}

void Grid::clear()
{
    if (map && !map->isEmpty())
    {
        int count = map->size();
        for (int i = 0; i < count; ++i)
        {
            Terrain* tile = map->values().at(i);
            scene->removeItem(tile);
            delete tile;
        }

        map->clear();
        delete map;
    }
}

void Grid::makeEmptyGrid()
{
    clear();

    map = new QMap<Position, Terrain*>();
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Position index (x,y);
            QRect rect (x + x*nodeSize, y + y*nodeSize, nodeSize, nodeSize);

            Terrain *tile = new Terrain(rect, TerrainType::None);
            map->insert(index, tile);
            scene->addItem(tile);
        }
    }
}

void Grid::makeRandomGrid()
{
    clear();

    map = new QMap<Position, Terrain*>();
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int type = Node::random(0, 6);

            Position index (x, y);
            QRect rect (x + x*nodeSize, y + y*nodeSize, nodeSize, nodeSize);            

            Terrain* tile;
            switch (type)
            {
                case 0:
                    tile = new Terrain (rect, TerrainType::Road);
                    break;

                case 1:
                    tile = new Terrain (rect, TerrainType::Grass);
                    break;

                case 2:
                    tile = new Terrain (rect, TerrainType::Hills);
                    break;

                case 3:
                    tile = new Terrain (rect, TerrainType::Forest);
                    break;

                case 4:
                    tile = new Terrain (rect, TerrainType::Mountains);
                    break;

                case 5:
                    tile = new Terrain (rect, TerrainType::Sand);
                    break;

                case 6:
                    tile = new Terrain (rect, TerrainType::Water);
                    break;

            }

            map->insert(index, tile);
            scene->addItem(tile);
        }
    }
}

Position Grid::randomPassableSpot()
{
    QList<Position> keys = map->keys();

    Position index = keys.at(Node::random(0, keys.length()));
    Terrain *tile = map->value(index);

    // TO DO:
    // STEP1. When creature moves to a tile  : oldPassable = passable, passable = false
    // STEP2. When creature moves from a tile: passable = oldPassable
    while (!tile->isPassable())
    {
        index = keys.at(Node::random(0, keys.length()));
        tile = map->value(index);
    }

    return index;
}

int Grid::getWidth()
{
    return width;
}

int Grid::getHeight()
{
    return height;
}

int Grid::getNodesize()
{
    return nodeSize;
}

void Grid::setWidth(int w)
{
    width = w;
}

void Grid::setHeight(int h)
{
    height = h;
}

void Grid::setNodesize(int s)
{
    nodeSize = s;
}

QGraphicsScene *Grid::getScene()
{
    return scene;
}

QGraphicsView *Grid::getView()
{
    return view;
}

void Grid::hideView()
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Terrain* terrain = at(Position(x,y));
            terrain->setHidden(true);
            terrain->update();
        }
    }
}

void Grid::showView(const Position& pos, int distance)
{
    for (int y = pos.y() - distance; y <= pos.y() + distance; ++y)
    {
        for (int x = pos.x() - distance; x <= pos.x() + distance; ++x)
        {
            Terrain* terrain = at(Position(x,y));
            if (terrain)
            {
                terrain->setHidden(false);
                terrain->update();
            }
        }
    }
}

void Grid::centerOn(const Position& pos)
{
    if (exists(pos))
    {
        view->ensureVisible(at(pos), nodeSize + 8, nodeSize + 8);
        view->centerOn(at(pos));
    }
}


bool Grid::exists(const Position& pos)
{
    return map->contains(pos);
}

Terrain *Grid::at(const Position& pos)
{
    return map->value(pos);
}

void Grid::replace(Terrain *oldV, Terrain *newV)
{
    Position oldK = map->key(oldV);

    // replace value in key-value of oldKey
    map->remove(oldK);
    map->insert(oldK, newV);

    // replace old item from scene with new one
    scene->removeItem(oldV);
    scene->addItem(newV);

    // delete old item
    delete oldV;
}

void Grid::updateSceneRect()
{
    int w = width*nodeSize + 7;
    int h = height*nodeSize + 7;
    scene->setSceneRect(QRect(0, 0, w, h));
}

QDataStream& operator<<(QDataStream &out, const Grid &from)
{
    out << from.width << from.height << from.nodeSize;

    QMap<Position, Terrain*> *map = from.map;
    for (int i = 0; i < map->size(); ++i)
    {
        QPoint pt = map->keys().at(i);
        Terrain *tile = map->values().at(i);

        out << pt << *tile;
    }

    return out;
}

QDataStream& operator>>(QDataStream &in, Grid &to)
{
    int width, height, nodeSize;
    in >> width >> height >> nodeSize;    

    to.setWidth(width);
    to.setHeight(height);
    to.setNodesize(nodeSize);
    to.makeEmptyGrid();

    Position position;
    Terrain terrain;
    for (int i = 0; i < width * height; ++i)
    {
        in >> position >> terrain;

        if (!terrain.isNull())
            to.replace(to.at(position), new Terrain(terrain.rect(), terrain.getTerrainType()));
    }

    return in;
}
