#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QRegExp>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class OptionsDialog : public QDialog
{
    Q_OBJECT
public:
    OptionsDialog(QWidget* parent = nullptr);
    ~OptionsDialog();

    int getX();
    int getY();
    int getSize();

private:
    void initGUI();

    int x;
    int y;
    int size;

    QLabel *lbl_x;
    QLabel *lbl_y;
    QLabel *lbl_size;

    QLineEdit *le_x;
    QLineEdit *le_y;
    QLineEdit *le_size;

    QPushButton *pb_ok;
    QPushButton *pb_cancel;

    QGridLayout *layout;

public slots:
    void onOk();
    void onCancel();
};

#endif // OPTIONSDIALOG_H
