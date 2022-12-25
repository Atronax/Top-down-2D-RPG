#include "position.h"

Position::Position() : QPoint()
{

}

Position::Position(int x, int y) : QPoint(x, y)
{

}

bool operator<(const Position &lhs, const Position &rhs)
{
    bool result = false;

    if ((lhs.y() < rhs.y()) || ((lhs.y() == rhs.y()) && (lhs.x() < rhs.x())))
        result = true;

    return result;
}

