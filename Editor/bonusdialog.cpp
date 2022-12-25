#include <QDebug>
#include <QRegExp>

#include "messageblink.h"
#include "bonusdialog.h"

BonusDialog::BonusDialog(QWidget* parent) : QDialog(parent)
{
    makeGUI();
}

BonusDialog::~BonusDialog()
{
    clearGUI();
}

const Stats &BonusDialog::getBonus()
{
    return bonus;
}

void BonusDialog::makeGUI()
{
    layout = new QGridLayout(this);

    label();
    bonusButtons();
    standardButtons();

    setLayout(layout);
}

void BonusDialog::label()
{
    lbl_top = new QLabel ("Choose parameters for this item");
    layout->addWidget(lbl_top, 0, 0, 1, 4, Qt::AlignCenter);
}

void BonusDialog::standardButtons()
{
    pb_ok = new QPushButton("Ok");
    pb_cancel = new QPushButton("Cancel");

    pb_ok->setAutoDefault(false);
    pb_cancel->setAutoDefault(false);

    connect (pb_ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect (pb_cancel, SIGNAL(clicked()), this, SLOT(reject()));

    layout->setRowMinimumHeight(6, 20);
    layout->addWidget(pb_ok, 7, 2, 1, 1);
    layout->addWidget(pb_cancel, 7, 3, 1, 1);
}

void BonusDialog::bonusButtons()
{
    const QStringList names = {"Name of the Bonus", "Speed", "Defence", "Range",  "Minimum Damage", "Maximum Damage",
                               "Current HP", "Maximum HP", "Chance to Hit", "Chance of Crit"};

    widgets = new QMap<QString, QPair<QPushButton*, QLineEdit*>>();
    for (int i = 0; i < names.size(); ++i)
    {
        QString text = names.at(i);
        int x = 1 + i/2;
        int y = (i%2 == 0) ? 0 : 2;

        createButton(text, x, y, 1, 2);
    }
}

bool BonusDialog::isAnyEditorActive()
{
    bool result = false;

    for (int i = 0; i < widgets->size(); ++i)
    {
        QPair<QPushButton*, QLineEdit*> pair = widgets->values().at(i);
        if (pair.second->isVisible())
            result = true;
    }

    return result;
}

void BonusDialog::clearGUI()
{
    for (int i = 0; i < widgets->size(); ++i)
    {
        QString name = widgets->keys().at(i);
        QPair<QPushButton*, QLineEdit*> pair = widgets->value(name);

        pair.first->deleteLater();
        pair.second->deleteLater();

        widgets->remove(name);
    }

    widgets->clear();
    delete widgets;

    lbl_top->deleteLater();
    pb_ok->deleteLater();
    pb_cancel->deleteLater();
    layout->deleteLater();
}

void BonusDialog::createButton(const QString &name, int x, int y, int w, int h)
{
    QPushButton* button = new QPushButton(name);
    button->setAutoDefault(false);
    button->setObjectName(name);

    QLineEdit* editor = new QLineEdit(name);
    editor->setObjectName(name);
    editor->hide();

    connect (button, SIGNAL(clicked()), this, SLOT(onButtonClick()));
    connect (editor, SIGNAL(returnPressed()), this, SLOT(onEditorEnter()));
    widgets->insert(name, QPair<QPushButton*, QLineEdit*>(button, editor));

    layout->addWidget(button, x, y, w, h);
}

QPushButton *BonusDialog::findButtonByName(const QString &name)
{
    QPushButton* button = nullptr;

    if (widgets->keys().contains(name))
        button = widgets->value(name).first;

    return button;
}

QLineEdit *BonusDialog::findEditorByName(const QString &name)
{
    QLineEdit* editor = nullptr;

    if (widgets->keys().contains(name))
        editor = widgets->value(name).second;

    return editor;
}

void BonusDialog::onButtonClick()
{
    QString name = static_cast<QPushButton*>(sender())->objectName();

    if (!isAnyEditorActive())
    {
        QPushButton* button = findButtonByName(name);
        QLineEdit  * editor = findEditorByName(name);

        layout->replaceWidget(button, editor);

        button->hide();
        editor->show();

        editor->setFocus();
    }
}

void BonusDialog::onEditorEnter()
{
    QString name = static_cast<QLineEdit*>(sender())->objectName();

    QPushButton* button = findButtonByName(name);
    QLineEdit  * editor = findEditorByName(name);

    if (parse(name, editor->text()))
    {
        layout->replaceWidget(editor, button);

        editor->hide();
        button->show();

        button->setFocus();
    }
}

bool BonusDialog::parse(const QString &type, const QString &string)
{
    // {"Name of the Bonus", "Speed", "Defence", "Range",  "Minimum Damage", "Maximum Damage",
    //  "Current HP", "Maximum HP", "Chance to Hit", "Chance of Crit"};

    qDebug() << "in parse function";

    bool result = false;

    if (type == "Name of the Bonus")
    {
        qDebug() << "in name block: " << string;

        QRegExp re ("[A-Za-z]{0,12}");
        if (re.exactMatch(string))
        {
            qDebug() << "exact match";
            bonus.setName(string);
            result = true;

            qDebug() << bonus.getName();
        }
        else
        {
            MessageBlink message ("No matches", 2000);
            message.start();

            qDebug() << "no matches";
        }
    }

    if (type == "Speed")
    {
        QRegExp re ("[0-9]{1,1}");
        if (re.exactMatch(string))
        {
            int value = string.toInt();
            bonus.setSpeed(value);
            result = true;
        }
    }

    if (type == "Defence")
    {
        QRegExp re ("[0-99]");
        if (re.exactMatch(string))
        {
            int value = string.toInt();
            bonus.setDefence(value);
            result = true;
        }
    }

    if (type == "Range")
    {
        QRegExp re ("[0-9]");
        if (re.exactMatch(string))
        {
            int value = string.toInt();

            if (value > bonus.getMAX_range())
                value = bonus.getMAX_range();

            bonus.setRange(value);
            result = true;
        }
    }

    if (type == "Minimum Damage")
    {
        QRegExp re ("[0-99]");
        if (re.exactMatch(string))
        {
            int value_low = string.toInt();
            int value_high = bonus.getDamage().y();

            if (value_high < value_low)
                value_high = value_low;

            bonus.setDamage(value_low, value_high);
            result = true;
        }
    }

    if (type == "Maximum Damage")
    {
        QRegExp re ("[0-99]");
        if (re.exactMatch(string))
        {
            int value_low = bonus.getDamage().x();
            int value_high = string.toInt();

            if (value_low > value_high)
                value_low = value_high;

            bonus.setDamage(value_low, value_high);
            result = true;
        }
    }

    if (type == "Current HP")
    {
        QRegExp re ("[0-999]");
        if (re.exactMatch(string))
        {
            int value_cur = string.toInt();
            int value_max = bonus.getHPMaximum();

            if (value_cur > value_max)
                value_cur = value_max;

            bonus.setHPCurrent(value_cur);
            bonus.setHPMaximum(value_max);
            result = true;
        }
    }

    if (type == "Maximum HP")
    {
        QRegExp re ("[0-999]");
        if (re.exactMatch(string))
        {
            int value_cur = bonus.getHPCurrent();
            int value_max = string.toInt();

            if (value_max < value_cur)
                value_cur = value_max;

            bonus.setHPCurrent(value_cur);
            bonus.setHPMaximum(value_max);
            result = true;
        }
    }

    if (type == "Chance to Hit")
    {
        QRegExp re ("[0-99]");
        if (re.exactMatch(string))
        {
            int value = string.toInt();

            if (value > bonus.getMAX_hitchance())
                value = bonus.getMAX_hitchance();

            bonus.setHitChance(value);
            result = true;
        }
    }

    if (type == "Chance of Crit")
    {
        QRegExp re ("[0-99]");
        if (re.exactMatch(string))
        {
            int value = string.toInt();

            if (value > bonus.getMAX_critchance())
                value = bonus.getMAX_critchance();

            bonus.setCritChance(value);
            result = true;
        }
    }

    return result;
}
