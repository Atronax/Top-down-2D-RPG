#include <QDebug>
#include <QPainter>

#include "statsview.h"

StatsView::StatsView(const QRect& g) : Node(g)
{
    setZValue(3);
    stats = nullptr;
}

StatsView::~StatsView()
{
    delete stats;
}

void StatsView::setStats(Stats* s)
{
    stats = s;
    updateRects();
}
void StatsView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // painter->fillRect(getRect(), QBrush(QColor(255, 255, 255, 64)));

    // painter->setFont(QFont("Times New Roman", 20, 10));
    // painter->drawText(r_name, stats.getName(), QTextOption(Qt::AlignCenter));

    qDebug() << "StatsView::paint invoked" << " - " << stats->getName();
    qDebug() << "StatsView::hp" << " - " << stats->getHPCurrent();

    painter->drawRect(r_maxHP);
    painter->fillRect(r_maxHP, QBrush(Qt::red));    
    painter->fillRect(r_curHP, QBrush(Qt::green));

    painter->drawText(r_maxHP.adjusted(0, 0, h_spacer, 0), QString::number(stats->getHPCurrent()));
}

void StatsView::updateRects()
{
    updateRect ("name");
    updateRect ("hp");
}

void StatsView::updateRect(const QString &what)
{
    QRectF canvas = rect();
    qreal x, y, w, h;

    if (what == "name")
    {
        x = canvas.x();
        y = canvas.y() + h_spacer;
        w = canvas.width();
        h = h_name;

        r_name = QRectF(x, y, w, h);
    }

    if (what == "hp")
    {
        x = canvas.x() + canvas.width() - w_hp*2;
        y = canvas.y();
        w = w_hp*2;
        h = canvas.height();

        r_maxHP = QRectF(x, y, w, h);

        double div = static_cast<double>(stats->getHPCurrent()) / static_cast<double>(stats->getHPMaximum());
        h *= div;

        r_curHP = QRectF(x, y + canvas.height() - h, w, h);
    }
}
