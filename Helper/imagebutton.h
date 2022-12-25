#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QPushButton>

class ImageButton : public QPushButton
{
    Q_OBJECT

public:
    ImageButton(const QString& text, QWidget* parent = nullptr);
    ~ImageButton();

    void setImage (const QString& imagePath);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void updateRectangles();

    QImage image;

    QRect  buttonRect;
    QRect  imageRect;
    const int shift = 1;
};

#endif // IMAGEBUTTON_H
