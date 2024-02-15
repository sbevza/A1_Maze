QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cc \
    controllers/maze_controller.cc \
    controllers/cave_controller.cc \
    views/mainwindow.cc \
    views/cave.cc \
    models/cave_model.cc \
    models/maze.cc \
    models/maze_generator.cc \
    models/maze_solver.cc
    

HEADERS += \
    views/cave.h \
    views/mainwindow.h \
    controllers/maze_controller.h \
    controllers/cave_controller.h \
    models/maze_generator.h \
    models/cave_model.h \
    models/maze.h \
    models/maze_solver.h

FORMS += \
    views/cave.ui \
    views/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
