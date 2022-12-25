#ifndef EDITORITEM_H
#define EDITORITEM_H

#include <QList>
#include <QFrame>
#include <QGridLayout>

#include "item.h"
#include "itemusable.h"
#include "itemequippable.h"
#include "itemview.h"

#include "editoritembasic.h"

class EditorItem : public QFrame
{
    Q_OBJECT

public:
    EditorItem(QWidget* parent = nullptr);
    ~EditorItem();

private:
    void makeItems();
    void makeGUI();

    void clearItems();
    void clearGUI();


    QList<Item*> *items;

    EditorItemBasic* basic;

    QPushButton* pb_next;
    QGridLayout* layout;
};

#endif // EDITORITEM_H
