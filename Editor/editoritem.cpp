#include "editoritem.h"

EditorItem::EditorItem(QWidget* parent) : QFrame(parent)
{
    makeItems();
    makeGUI();
}

EditorItem::~EditorItem()
{
    clearItems();
    clearGUI();
}

void EditorItem::makeItems()
{
    // TODO: make save and load functions
    // so we can load the db and add new elements to it
    items = new QList<Item*>();

}

void EditorItem::makeGUI()
{
    basic = new EditorItemBasic;

    pb_next = new QPushButton ("Next");
    pb_next->setEnabled(false);

    layout = new QGridLayout(this);
    layout->addWidget(basic, 0, 0, 3, 3);
    layout->addWidget(pb_next, 3, 2, 1, 1);
    setLayout(layout);

    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
}

void EditorItem::clearItems()
{
    if (items && !items->isEmpty())
    {
        for (int i = 0; i < items->size(); ++i)
            delete items->at(i);

        items->clear();
        delete items;
    }
}

void EditorItem::clearGUI()
{
    basic->deleteLater();

    pb_next->deleteLater();
    layout->deleteLater();
}
