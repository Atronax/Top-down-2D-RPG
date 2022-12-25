#include <QPainter>
#include <QGraphicsWidget>
#include <QDebug>

#include "creature.h"

Creature::Creature(const QRect& r, const Position &p)
    : Node(r), statsView(r)
{
    setZValue(2);
    position = p;
}

Creature::~Creature()
{
}

void Creature::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Terrain *block = grid->at(Position(position.x(), position.y()));
    if (block && !block->isHidden())
    {
        painter->drawImage(rect(), skin);
        statsView.paint(painter, option, widget);
    }
}

// STATS
Stats& Creature::getStats()
{
    return stats;
}

void Creature::setStats(const Stats& input)
{
    stats = input;

    // 3x3 tiles:
    // QRect c = rect();
    // QRect r = QRect(c.x() - c.width(), c.y() - c.height(), 3*c.width(), 3*c.height()));
    statsView.setRect(rect());
    statsView.setStats(&stats);
}

void Creature::updateStatsView()
{
    statsView.updateRects();
    grid->getView()->viewport()->repaint();
}

// VIEW
const QImage &Creature::getSkin()
{
    return skin;
}

void Creature::setSkin(const QImage &input)
{
    skin = input;
}

// LOCATION AND MOVE FUNCTIONALITY
Grid *Creature::getGrid()
{
    return grid;
}

void Creature::setGrid(Grid *g)
{
    grid = g;
    if (stats.getType() == "Player")
        updateView();
}

const Position &Creature::getPosition()
{
    return position;
}

void Creature::setPosition(const Position& input)
{
    position = input;
}

bool Creature::canMove(Movement direction)
{
    bool result = false;

    Terrain* terrain;
    switch (direction)
    {
        case Movement::North:
            terrain = grid->at(Position(position.x(), position.y() - 1));
            break;

        case Movement::East:
            terrain = grid->at(Position(position.x() + 1, position.y()));
            break;

        case Movement::South:
            terrain = grid->at(Position(position.x(), position.y() + 1));
            break;

        case Movement::West:
            terrain = grid->at(Position(position.x() - 1, position.y()));
            break;
    }

    if (terrain && terrain->isPassable())
        result = true;

    return result;
}

void Creature::move(Movement direction)
{
    Node* node;
    switch (direction)
    {
        case Movement::North:
            node = grid->at(Position(position.x(), position.y() - 1));
            position.setX(position.x());
            position.setY(position.y() - 1);
            break;

        case Movement::East:
            node = grid->at(Position(position.x() + 1, position.y()));
            position.setX(position.x() + 1);
            position.setY(position.y());
            break;

        case Movement::South:
            node = grid->at(Position(position.x(), position.y() + 1));
            position.setX(position.x());
            position.setY(position.y() + 1);
            break;

        case Movement::West:
            node = grid->at(Position(position.x() - 1, position.y()));
            position.setX(position.x() - 1);
            position.setY(position.y());
            break;
    }

    setRect(node->rect());
    updateView();
}

void Creature::updateView()
{
    statsView.setRect(rect());
    statsView.updateRects();

    grid->hideView();
    grid->showView(position, stats.getRange());
    grid->centerOn(position);
}
