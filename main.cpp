#include <QApplication>
#include <QDateTime>

#include "world.h"
#include "editor.h"
#include "editoritem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    
    qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch() / 1000));

    World w;
    w.show();

    // Editor e;
    // e.show();

    // EditorItem ei;
    // ei.show();

    return a.exec();
}
