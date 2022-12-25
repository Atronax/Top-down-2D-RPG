#ifndef GRID_H
#define GRID_H

#include <QMap>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "position.h"
#include "terrain.h"

class Grid
{
public:
    Grid  (QGraphicsScene *scene, QGraphicsView *view);
    ~Grid ();

    QGraphicsScene* getScene();
    QGraphicsView * getView();

    // Fog of war functionality
    void hideView ();
    void showView (const Position& pos, int distance);
    void centerOn (const Position& pos);
    void updateSceneRect();

    // Seekers functions
    Position randomPassableSpot();
    bool exists(const Position& pos);
    Terrain* at(const Position& pos);

    // Basic information
    int getWidth();
    int getHeight();
    int getNodesize();

    void setWidth(int width);
    void setHeight(int height);
    void setNodesize(int size);

    // Editor functionality
    void makeEmptyGrid();
    void makeRandomGrid();
    void replace(Terrain* oldTile, Terrain* newTile);

    friend QDataStream& operator<< (QDataStream&, const Grid&);
    friend QDataStream& operator>> (QDataStream&, Grid&);

private:
    void clear();

    QGraphicsScene *scene;
    QGraphicsView  *view;
    QMap<Position, Terrain*> *map;

    int width = 8;
    int height = 8;
    int nodeSize = 40;
};

#endif // GRID_H
