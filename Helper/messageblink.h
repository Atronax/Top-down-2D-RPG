#ifndef MESSAGEBLINK_H
#define MESSAGEBLINK_H

#include <QTimer>
#include <QMessageBox>

class MessageBlink : public QObject
{
    Q_OBJECT
public:
    MessageBlink(const QString& text, int duration, QWidget *parent = nullptr);
    ~MessageBlink();

    void start();

private:
    int duration;
    QString text;

    QMessageBox box;
    QTimer timer;

    qreal opacity;
    int tick;

signals:

public slots:
    void changeOpacity();
};

#endif // MESSAGEBLINK_H
