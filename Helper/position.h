#ifndef POSITION_H
#define POSITION_H

#include <QPoint>

class Position : public QPoint
{
public:
    Position();
    Position(int x, int y);

    friend bool operator< (const Position& lhs, const Position& rhs);
};

#endif // POSITION_H
