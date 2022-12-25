#include <QDebug>

#include "world.h"

World::World(QWidget *parent) : QFrame(parent)
{
    makeScene();

    // makeTest();
    makeGrid();
    makeGridObjects();
    makePlayer();

}

World::~World()
{
    scene->deleteLater();
    view->deleteLater();

    clearGrid();
}

void World::keyPressEvent(QKeyEvent *ev)
{
    player->keyPressEvent(ev);
}

void World::save(const QString &filename)
{
    QFile file (filename);

    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream (&file);
        stream << *grid;

        file.close();
    }
}

void World::load(const QString &filename)
{
    QFile file (filename);

    if (!file.exists())
        return;

    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream stream (&file);
        stream >> *grid;

        file.close();
    }
}

void World::makeScene()
{
    scene = new QGraphicsScene (QRectF(0, 0, 481, 481), this);
    scene->setBackgroundBrush(Qt::black);

    view  = new QGraphicsView (scene, this);
    view->setRenderHint(QPainter::Antialiasing, true);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    

    layout = new QGridLayout(this);
    layout->addWidget(view);
    setLayout(layout);
}

void World::makeTest()
{
    QGraphicsRectItem* r;
    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
        {
            r = scene->addRect(x + x*30, y + y*30, 30, 30);
            r->setBrush(Qt::white);
            r->setFlags(QGraphicsItem::ItemIsMovable);
        }
    }

    QGraphicsRectItem* m = scene->addRect(30, 30, 30, 30);
    m->setParentItem(r);
    m->setBrush(Qt::green);
    m->setFlags(QGraphicsItem::ItemIsMovable);

    QGraphicsRectItem* big = scene->addRect(0, 0, 90, 90);
    big->setParentItem(m);
    big->setBrush(Qt::red);
    big->setFlags(QGraphicsItem::ItemIsMovable);

    /*
    QGraphicsRectItem* r1 = scene->addRect(50, 50, 50, 50);
    QGraphicsRectItem* r2 = scene->addRect(120, 50, 50, 50);
    QGraphicsRectItem* r3 = scene->addRect(190, 50, 50, 50);

    r1->setBrush(QColor(50, 20, 20));
    r2->setBrush(QColor(50, 20, 20));
    r3->setBrush(QColor(50, 20, 20));

    r1->setFlags(QGraphicsItem::ItemIsMovable);
    r2->setFlags(QGraphicsItem::ItemIsMovable);
    r3->setFlags(QGraphicsItem::ItemIsMovable);

    QGraphicsRectItem* rr1 = scene->addRect(50, 50, 10, 10);
    QGraphicsRectItem* rr2 = scene->addRect(120, 50, 10, 10);
    QGraphicsRectItem* rr3 = scene->addRect(190, 50, 10, 10);

    rr1->setBrush(QColor(250, 200, 200));
    rr2->setBrush(QColor(200, 250, 200));
    rr3->setBrush(QColor(200, 200, 250));

    rr1->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    rr2->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    rr3->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    rr1->setZValue(2.0);
    rr2->setZValue(2.0);
    rr3->setZValue(2.0);

    rr1->setParentItem(r1);
    rr2->setParentItem(r2);
    rr3->setParentItem(r3);
    */

}

void World::makeGrid()
{
    grid  = new Grid(scene, view);

    load("test.map");
    // grid->makeRandomGrid();
    grid->updateSceneRect();
}

void World::makeGridObjects()
{
    gridObjects = new GridObjects(scene, view);

    int cnt = 3;
    for (int i = 0; i < cnt; ++i)
    {
        Position pos = grid->randomPassableSpot();
        QRect rect   = grid->at(pos)->rect();

        Enemy* spider = gridObjects->makeEnemy(rect, pos, EnemyType::Spider);
        spider->setGrid(grid);
    }
}

void World::makePlayer()
{
    Position pos = grid->randomPassableSpot();
    Node *node = grid->at(pos);

    player = new Player(node->rect(), pos);
    player->setGrid(grid);
    player->setGridObjects(gridObjects);

    scene->addItem(player);
}

void World::clearGrid()
{
    scene->removeItem(player);
    delete player;
    delete gridObjects;
    delete grid;
}
