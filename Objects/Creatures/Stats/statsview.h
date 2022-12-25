#ifndef STATSVIEW_H
#define STATSVIEW_H

#include "stats.h"
#include "node.h"

class StatsView : public Node
{
public:    
    StatsView(const QRect& geometry);
    ~StatsView();

    void setStats(Stats* stats);
    void updateRects();

    // QGraphicsItem interface
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:    
    void updateRect (const QString& what);

    Stats* stats;

    const int h_spacer = 5;
    const int h_name = 30;
    const int w_hp = 5, h_hp = 15;

    QRectF r_name;
    QRectF r_curHP, r_maxHP;

};

#endif // STATSVIEW_H
