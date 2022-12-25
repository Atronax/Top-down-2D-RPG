#ifndef EDITOR_H
#define EDITOR_H

#include <QFrame>
#include <QToolBar>
#include <QPushButton>
#include <QGraphicsScene>
#include "graphicsview.h"
#include <QGridLayout>
#include <QMouseEvent>

#include "grid.h"
#include "optionsdialog.h"

class Editor : public QFrame
{
    Q_OBJECT
public:
    Editor(QWidget* parent = nullptr);
    ~Editor();

private:
    void save(const QString& filename);
    void load(const QString& filename);

    void changeAt(int x, int y, TerrainType newType);

    void makeMap();
    void makeGUI();

    TerrainType terrainType;

    // canvas to draw on and map data
    QGraphicsScene* scene;
    GraphicsView* view;
    Grid* map;

    // header
    QToolBar* tb_header;

    // generator buttons, save and load
    QPushButton* pb_road;
    QPushButton* pb_grass;
    QPushButton* pb_hills;
    QPushButton* pb_forest;
    QPushButton* pb_mountains;
    QPushButton* pb_sand;
    QPushButton* pb_water;
    QPushButton* pb_save;
    QPushButton* pb_load;

    // layouts
    QGridLayout* layout;
    QHBoxLayout* buttons;



public slots:
    void newGrid();
    void typeChosen();
    void onMouseMove (const QPoint& position);

    void onSave();
    void onLoad();
};

#endif // EDITOR_H
