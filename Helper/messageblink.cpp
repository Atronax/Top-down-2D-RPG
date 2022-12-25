#include <QDebug>
#include "messageblink.h"

MessageBlink::MessageBlink(const QString& _text, int _duration, QWidget* parent) : QObject(parent)
{
    text = _text;
    duration = _duration;
}

MessageBlink::~MessageBlink()
{

}


void MessageBlink::start()
{
    if (text.isEmpty() || duration < 0)
        return;

     tick = 0;
     opacity = 0.0;

     box.setWindowFlags(Qt::FramelessWindowHint);
     box.setStandardButtons(QMessageBox::NoButton);
     box.setIcon(QMessageBox::NoIcon);
     box.setWindowOpacity(opacity);
     box.setText(text);
     box.show();

     timer.setInterval(duration/80);
     connect(&timer, SIGNAL(timeout()), this, SLOT(changeOpacity()));
     timer.start();
}

void MessageBlink::changeOpacity()
{
    ++tick;
    if (tick == 80)
    {
        box.hide();
        timer.stop();
        disconnect(&timer, SIGNAL(timeout()), this, SLOT(changeBoxOpacity()));
    }

    opacity = box.windowOpacity();
    if (tick <= 15)
        opacity += 0.08;
    else if (tick >= 65)
        opacity -= 0.08;

    box.setWindowOpacity(opacity);
}
