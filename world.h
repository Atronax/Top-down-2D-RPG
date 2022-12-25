#ifndef WORLD_H
#define WORLD_H

#include <QFrame>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>

#include "grid.h"
#include "gridobjects.h"
#include "player.h"
#include "itemview.h"

class World : public QFrame
{
    Q_OBJECT

public:
    World(QWidget *parent = nullptr);
    ~World();

    void keyPressEvent(QKeyEvent* ev);

private:
    void save (const QString& filename);
    void load (const QString& filename);

    void clearGrid();
    void makeScene();
    void makeTest();
    void makeGrid();
    void makeGridObjects();
    void makePlayer();

    QGraphicsScene* scene;
    QGraphicsView* view;

    Grid *grid;
    GridObjects *gridObjects;
    Player *player;

    QGridLayout *layout;

signals:

public slots:
};

#endif // WORLD_H
