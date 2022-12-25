#-------------------------------------------------
#
# Project created by QtCreator 2018-10-11T13:14:32
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = 2D_RPG
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    world.cpp \
    Aggregates/grid.cpp \
    Aggregates/gridobjects.cpp \
    Editor/editor.cpp \
    Editor/graphicsview.cpp \
    Editor/optionsdialog.cpp \
    Helper/position.cpp \
    Objects/Creatures/Stats/stats.cpp \
    Objects/Creatures/Stats/statsview.cpp \
    Objects/Creatures/creature.cpp \
    Objects/Creatures/enemy.cpp \
    Objects/Creatures/player.cpp \
    Objects/Terrain/terrain.cpp \
    Objects/node.cpp \
    Objects/Items/item.cpp \
    Objects/Items/itemview.cpp \
    Objects/Items/itemusable.cpp \
    Objects/Items/itemequippable.cpp \
    Editor/editoritem.cpp \
    Editor/editoritembasic.cpp \
    Helper/imagebutton.cpp \
    Editor/bonusdialog.cpp \
    Helper/messageblink.cpp

HEADERS += \
    world.h \
    Aggregates/grid.h \
    Aggregates/gridobjects.h \
    Editor/editor.h \
    Editor/graphicsview.h \
    Editor/optionsdialog.h \
    Helper/enums.h \
    Helper/position.h \
    Objects/Creatures/Stats/stats.h \
    Objects/Creatures/Stats/statsview.h \
    Objects/Creatures/creature.h \
    Objects/Creatures/enemy.h \
    Objects/Creatures/player.h \
    Objects/Terrain/terrain.h \
    Objects/node.h \
    Objects/Items/item.h \
    Objects/Items/itemview.h \
    Objects/Items/itemequippable.h \
    Objects/Items/itemusable.h \
    Editor/editoritem.h \
    Editor/editoritembasic.h \
    Helper/imagebutton.h \
    Editor/bonusdialog.h \
    Helper/messageblink.h

INCLUDEPATH += $$PWD/aggregates \
               $$PWD/editor \
               $$PWD/helper \
               $$PWD/objects \
               $$PWD/objects/creatures \
               $$PWD/objects/creatures/stats \
               $$PWD/objects/items \
               $$PWD/objects/terrain


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
