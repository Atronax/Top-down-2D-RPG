#ifndef CREATURE_H
#define CREATURE_H

#include "enums.h"
#include "node.h"
#include "grid.h"
#include "stats.h"
#include "statsview.h"

class Creature : public Node
{
public:
    Creature(const QRect& rect, const Position& pos);
    ~Creature();

    Stats& getStats();    
    void setStats(const Stats& input);

    void updateStatsView();

    const QImage& getSkin();
    void setSkin (const QImage& input);

    const Position& getPosition();
    void setPosition(const Position& input);

    Grid* getGrid();
    void setGrid(Grid* grid);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    bool canMove(Movement direction);
    void move(Movement direction);

private:
    void updateView();

    QImage skin;

    // LOCATION
    Grid*  grid;
    Position position;

    Stats stats;
    StatsView statsView;
};

#endif // CREATURE_H
