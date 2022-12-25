#include <QDebug>

#include "graphicsview.h"

GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent) : QGraphicsView (scene, parent)
{

}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        position = ev->globalPos();
        emit mouseMove(position);
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *ev)
{
    position = ev->globalPos();
    emit mouseMove(position);
}
