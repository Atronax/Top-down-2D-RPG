#include <QDebug>
#include <QDataStream>
#include <QMouseEvent>

#include "editor.h"

Editor::Editor(QWidget* parent) : QFrame(parent)
{
    makeMap();
    makeGUI();

    terrainType = TerrainType::None;
}

Editor::~Editor()
{       
    scene->deleteLater();
    view->deleteLater();
    delete map;

    tb_header->deleteLater();

    pb_road->deleteLater();
    pb_grass->deleteLater();
    pb_hills->deleteLater();
    pb_forest->deleteLater();
    pb_mountains->deleteLater();
    pb_sand->deleteLater();
    pb_water->deleteLater();
    pb_save->deleteLater();
    pb_load->deleteLater();

    layout->deleteLater();
    buttons->deleteLater();

}

void Editor::save(const QString &filename)
{
    QFile file (filename);

    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream (&file);
        stream << *map;

        file.close();
    }
}

void Editor::load(const QString &filename)
{
    QFile file (filename);

    if (!file.exists())
        return;

    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream stream (&file);
        stream >> *map;

        file.close();
    }
}

void Editor::makeMap()
{
    scene = new QGraphicsScene(0, 0, 480, 480, this);    
    view = new GraphicsView(scene, this);
    map = new Grid(scene, view);
    map->updateSceneRect();

    connect (view, SIGNAL(mouseMove(const QPoint&)), this, SLOT(onMouseMove(const QPoint&)));
}

void Editor::makeGUI()
{
    tb_header = new QToolBar("Top menu");
    QAction* newGrid = tb_header->addAction("New Grid");

    connect (newGrid, SIGNAL(triggered()), this, SLOT(newGrid()));

    pb_road = new QPushButton("Road");
    pb_grass = new QPushButton("Grass");
    pb_hills = new QPushButton("Hills");
    pb_forest = new QPushButton("Forest");
    pb_mountains = new QPushButton("Mountains");
    pb_sand = new QPushButton("Sand");
    pb_water = new QPushButton("Water");
    pb_save = new QPushButton("SAVE");
    pb_load = new QPushButton("LOAD");

    connect (pb_road, SIGNAL(clicked()), this, SLOT(typeChosen()));
    connect (pb_grass, SIGNAL(clicked()), this, SLOT(typeChosen()));
    connect (pb_hills, SIGNAL(clicked()), this, SLOT(typeChosen()));
    connect (pb_forest, SIGNAL(clicked()), this, SLOT(typeChosen()));
    connect (pb_mountains, SIGNAL(clicked()), this, SLOT(typeChosen()));
    connect (pb_sand, SIGNAL(clicked()), this, SLOT(typeChosen()));
    connect (pb_water, SIGNAL(clicked()), this, SLOT(typeChosen()));
    connect (pb_save, SIGNAL(clicked()), this, SLOT(onSave()));
    connect (pb_load, SIGNAL(clicked()), this, SLOT(onLoad()));

    buttons = new QHBoxLayout;
    buttons->addWidget(pb_road);
    buttons->addWidget(pb_grass);
    buttons->addWidget(pb_hills);
    buttons->addWidget(pb_forest);
    buttons->addWidget(pb_mountains);
    buttons->addWidget(pb_sand);
    buttons->addWidget(pb_water);

    buttons->addWidget(pb_save);
    buttons->addWidget(pb_load);

    layout = new QGridLayout (this);
    layout->addWidget(tb_header, 0, 0, 1, 10);
    layout->addWidget(view, 1, 0, 8, 10);
    layout->addLayout(buttons, 9, 0, 1, 10);
    setLayout(layout);
}

void Editor::newGrid()
{
    OptionsDialog dlg;

    if (dlg.exec())
    {
        int w = dlg.getX();
        int h = dlg.getY();
        int s = dlg.getSize();

        map->setWidth(w);
        map->setHeight(h);
        map->setNodesize(s);
        map->makeEmptyGrid();
        map->updateSceneRect();


        qDebug() << w << " : " << h << " : " << s;
    }
}

void Editor::typeChosen()
{
    QString type = static_cast<QPushButton*>(sender())->text();

    if (type == "Road")
        terrainType = TerrainType::Road;
    else if (type == "Grass")
        terrainType = TerrainType::Grass;
    else if (type == "Hills")
        terrainType = TerrainType::Hills;
    else if (type == "Forest")
        terrainType = TerrainType::Forest;
    else if (type == "Mountains")
        terrainType = TerrainType::Mountains;
    else if (type == "Sand")
        terrainType = TerrainType::Sand;
    else if (type == "Water")
        terrainType = TerrainType::Water;

    if (terrainType != TerrainType::None)
        qDebug() << "current type chosen";

}

void Editor::onMouseMove(const QPoint &position)
{
    if (view->hasFocus())
    {
        QPoint mouse = view->mapFromGlobal(position);

        Terrain *tile = dynamic_cast<Terrain*>(view->itemAt(mouse.x(), mouse.y()));
        if (tile && tile->getTerrainType() != terrainType)
            changeAt(mouse.x(), mouse.y(), terrainType);
    }
}

void Editor::changeAt(int x, int y, TerrainType type)
{
    qDebug() << x << " : " << y << " -" << "newType";

    if (type != TerrainType::None)
    {
        QGraphicsItem* item = view->itemAt(x, y);
        if (item)
        {
            Terrain* o = dynamic_cast<Terrain*>(item);
            o->setTerrainType(TerrainType::None);
            o->setTerrainType(type);
            o->update();
        }
    }
}


void Editor::onSave()
{
    save("test.map");
    qDebug() << "saved to \"test.map\"";
}

void Editor::onLoad()
{
    load("test.map");
    qDebug() << "loaded from \"test.map\"";
}
