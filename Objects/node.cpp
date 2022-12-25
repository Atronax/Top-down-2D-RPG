#include <QDebug>
#include <QPainter>

#include "node.h"

Node::Node()
{
    setZValue(0);
    geometry = QRect();
}

Node::Node(const QRect& rect) : QGraphicsItem (nullptr)
{
    setZValue(0);
    geometry = rect;

}

Node::~Node()
{

}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr)
{
    Q_UNUSED (option);
    Q_UNUSED (widget);

    painter->drawRect(geometry);
}


int Node::random(int start, int end)
{
    return start + qrand()%(end - start + 1);
}

const QRect &Node::rect()
{
    return geometry;
}

void Node::setRect(const QRect &r)
{
    geometry = r;
}

QString Node::toString()
{
    int x = geometry.x();
    int y = geometry.y();
    int w = geometry.width();
    int h = geometry.height();

    return QString("Rect: %1,%2,%3,%4 --- %5").arg(x).arg(y).arg(w).arg(h);
}

QRectF Node::boundingRect() const
{
    return geometry;
}

QDataStream& operator<<(QDataStream &out, const Node &from)
{
    out << from.geometry;

    return out;
}

QDataStream& operator>>(QDataStream &in, Node &to)
{
    QRect rect;
    in >> rect;

    to.geometry = rect;

    return in;
}
