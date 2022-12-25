#ifndef EDITORITEMBASIC_H
#define EDITORITEMBASIC_H

#include <QFrame>
#include <QTextEdit>
#include <QPushButton>
#include "imagebutton.h"
#include <QGridLayout>

#include "item.h"

class EditorItemBasic : public QFrame
{
    Q_OBJECT

public:
    EditorItemBasic(QWidget* parent = nullptr);
    ~EditorItemBasic();

private:
    void makeItem();
    void makeGUI();

    void clearItem();
    void clearGUI();

    ImageButton* ib_img;
    QPushButton* pb_name;
    QPushButton* pb_bonus;
    QPushButton* pb_description;

    QHBoxLayout* layout_top;
    QVBoxLayout* layout;

public slots:
    void onImageClicked();

    void onBonusClicked();
};

#endif // EDITORITEMBASIC_H
