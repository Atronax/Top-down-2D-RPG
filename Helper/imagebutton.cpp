#include <QFileInfo>
#include <QPainter>
#include <QDebug>

#include "imagebutton.h"

ImageButton::ImageButton(const QString& text, QWidget *parent) : QPushButton (text, parent)
{
}

ImageButton::~ImageButton()
{
}

void ImageButton::setImage(const QString& imagePath)
{
    if (QFileInfo::exists(imagePath))
    {
        image = QImage(imagePath);
        updateRectangles();
    }

    qDebug() << image.size();
}

void ImageButton::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);

    if (!image.isNull())
    {
        QPainter painter(this);
        painter.drawRect(buttonRect);
        painter.drawImage(imageRect, image);
    }
    else
        QPushButton::paintEvent(ev);
}

void ImageButton::updateRectangles()
{
    buttonRect = QRect(0, 0, width() - 1, height() - 1);
    imageRect = buttonRect.adjusted(shift, shift, 0, 0);
}
