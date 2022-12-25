#include <QPainter>
#include "itemview.h"

ItemView::ItemView(const QRect &r, const Position &p, Item *i) : Node(r)
{
    position = p;
    setItem(i);
}

ItemView::~ItemView()
{

}

void ItemView::setRect(const QRect &r)
{
    Node::setRect(r);
}

void ItemView::setItem(Item *i)
{
    if (i)
    {
        item = i;
        image = QImage(item->skinPath());
    }
}

void ItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawRect(rect());
    if (!image.isNull())
        painter->drawImage(rect().adjusted(2, 2, -2, -2), image);
    else
        painter->drawText(rect(), item->getName());
}
