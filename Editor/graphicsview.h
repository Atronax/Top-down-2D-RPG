#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);
    ~GraphicsView();

    void mousePressEvent (QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);

private:
    QPoint position;

signals:
    void mouseMove (const QPoint& pos);
};

#endif // GRAPHICSVIEW_H
