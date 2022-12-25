#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
class Node : public QGraphicsItem
{
public:
    Node();
    Node(const QRect& rect);
    ~Node();   

    static int random (int start, int end);

    const QRect& rect ();
    void setRect (const QRect& rectangle);

    friend QDataStream& operator<< (QDataStream&, const Node&);
    friend QDataStream& operator>> (QDataStream&, Node&);

    // QGraphicsItem interface
    QRectF boundingRect() const;
    virtual void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    virtual QString toString();

protected:
    QRect geometry;
};

#endif // NODE_H
