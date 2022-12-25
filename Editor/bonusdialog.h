#ifndef BONUSDIALOG_H
#define BONUSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>

#include "stats.h"

class BonusDialog : public QDialog
{
    Q_OBJECT
public:
    BonusDialog(QWidget* parent = nullptr);
    ~BonusDialog();

    const Stats& getBonus();

private:
    void message (const QString& text, int duration);
    bool parse (const QString& type, const QString& string);
    void makeGUI();
    void clearGUI();

    void label();
    void standardButtons();
    void bonusButtons();

    Stats bonus;

    // Messaging subsystem


    // User interface    
    bool isAnyEditorActive();
    QPushButton* findButtonByName(const QString& name);
    QLineEdit  * findEditorByName(const QString& name);
    void createButton(const QString& name, int x, int y, int w, int h);

    QLabel* lbl_top;
    QMap<QString, QPair<QPushButton*, QLineEdit*>> *widgets;
    QPushButton *pb_ok, *pb_cancel;
    QGridLayout* layout;

public slots:
    void onButtonClick();
    void onEditorEnter();
};

#endif // BONUSDIALOG_H
