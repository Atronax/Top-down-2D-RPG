#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include <QObject>
#include <QTimer>


#include "position.h"
#include "node.h"
#include "item.h"

class ItemView : public QObject, public Node
{
    Q_OBJECT
public:
    ItemView(const QRect& rect, const Position& position, Item* item);
    ~ItemView();

    void setRect(const QRect& rect);
    void setItem(Item* item);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    Item* item;

    QImage image;
    Position position;

public slots:

};

#endif // ITEMVIEW_H
