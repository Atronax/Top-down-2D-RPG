#include <QDebug>
#include <QFileDialog>

#include "editoritembasic.h"
#include "bonusdialog.h"

EditorItemBasic::EditorItemBasic(QWidget* parent) : QFrame(parent)
{
    makeGUI();
}

EditorItemBasic::~EditorItemBasic()
{
    clearGUI();
}

void EditorItemBasic::makeGUI()
{
    ib_img = new ImageButton("Image");
    pb_name = new QPushButton("Name");
    pb_bonus = new QPushButton("Bonus");
    pb_description = new QPushButton("Description");

    connect (ib_img, SIGNAL(clicked()), this, SLOT(onImageClicked()));

    connect (pb_bonus, SIGNAL(clicked()), this, SLOT(onBonusClicked()));

    ib_img->setFixedSize(64, 64);
    pb_name->setFixedSize(128, 64);
    pb_bonus->setFixedSize(256, 128);
    pb_description->setFixedSize(256, 128);

    layout_top = new QHBoxLayout;
    layout_top->addWidget(ib_img);
    layout_top->addSpacing(64 - 6);
    layout_top->addWidget(pb_name);
    layout_top->addStretch(1);

    layout = new QVBoxLayout(this);
    layout->addLayout(layout_top);
    layout->addWidget(pb_bonus);
    layout->addWidget(pb_description);
    layout->addStretch(1);
    setLayout(layout);


}

void EditorItemBasic::clearItem()
{

}

void EditorItemBasic::clearGUI()
{
    ib_img->deleteLater();
    pb_name->deleteLater();
    pb_bonus->deleteLater();
    pb_description->deleteLater();

    layout->deleteLater();
}

void EditorItemBasic::onImageClicked()
{
    QString imagePath = QFileDialog::getOpenFileName(nullptr, "Choose image for this item", QString(), "*.jpeg *.jpg *.png");
    ib_img->setImage(imagePath);

    qDebug() << imagePath;
}

void EditorItemBasic::onBonusClicked()
{
    BonusDialog bd;
    if (bd.exec())
    {
        // get Stats object and set it as a bonus
        // show another widget instead of pb_bonus that reveals chosen parameters
    }
}
