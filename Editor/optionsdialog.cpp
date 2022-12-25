#include <QMessageBox>

#include "optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget* parent) : QDialog(parent)
{
    initGUI();
}

OptionsDialog::~OptionsDialog()
{
    lbl_x->deleteLater();
    lbl_y->deleteLater();
    lbl_size->deleteLater();

    le_x->deleteLater();
    le_y->deleteLater();
    le_size->deleteLater();

    pb_ok->deleteLater();
    pb_cancel->deleteLater();

    layout->deleteLater();
}

int OptionsDialog::getX()
{
    return x;
}

int OptionsDialog::getY()
{
    return y;
}

int OptionsDialog::getSize()
{
    return size;
}

void OptionsDialog::initGUI()
{
    lbl_x = new QLabel ("X:");
    lbl_y = new QLabel ("Y:");
    lbl_size = new QLabel ("Size: ");

    le_x = new QLineEdit ("0");
    le_y = new QLineEdit ("0");
    le_size = new QLineEdit ("40");

    pb_ok = new QPushButton ("Ok");
    pb_cancel = new QPushButton ("Cancel");

    connect (pb_ok, SIGNAL(clicked()), this, SLOT(onOk()));
    connect (pb_cancel, SIGNAL(clicked()), this, SLOT(onCancel()));

    layout = new QGridLayout (this);
    layout->addWidget(lbl_x, 0, 0);
    layout->addWidget(le_x, 0, 1);
    layout->addWidget(lbl_y, 1, 0);
    layout->addWidget(le_y, 1, 1);
    layout->addWidget(lbl_size, 2, 0);
    layout->addWidget(le_size, 2, 1);
    layout->addWidget(pb_ok, 3, 2);
    layout->addWidget(pb_cancel, 3, 3);
    setLayout(layout);
}

void OptionsDialog::onOk()
{
    QString str_x = le_x->text();
    QString str_y = le_y->text();
    QString str_s = le_size->text();

    QRegExp re ("[0-9]{1,3}");
    if (re.exactMatch(str_x) && re.exactMatch(str_y) && re.exactMatch(str_s))
    {
        x = str_x.toInt();
        y = str_y.toInt();
        size = str_s.toInt();

        if ((x == 0 && y == 0) || (size < 40))
            reject();
        else
            accept();
    }
    else
    {
        QMessageBox message;
        message.setText("Введите числовые значения от 0 до 999. Size не может быть менее 40. ");
        message.exec();
    }
}

void OptionsDialog::onCancel()
{
    reject();
}
