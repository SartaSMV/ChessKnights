QT       += core gui
QT       += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ChessBoard/chessboard.cpp \
    ChessPlayers/chessbot.cpp \
    ChessPlayers/chessplayer.cpp \
    ChessPlayers/chessuser.cpp \
    Figure/chessbishop.cpp \
    Figure/chessbishop.cpp \
    Figure/chessfigure.cpp \
    Figure/chessfigure.cpp \
    Figure/chessknight.cpp \
    Figure/chessknight.cpp \
    Figure/chessrook.cpp \
    Figure/chessrook.cpp \
    Figure/figure.cpp \
    Figure/figure.cpp \
    Figure/prize.cpp \
    Figure/prize.cpp \
    StartWindow/startwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    ratingboard.cpp

HEADERS += \
    ChessBoard/chessboard.h \
    ChessPlayers/chessbot.h \
    ChessPlayers/chessplayer.h \
    ChessPlayers/chessuser.h \
    Figure/chessbishop.h \
    Figure/chessbishop.h \
    Figure/chessfigure.h \
    Figure/chessfigure.h \
    Figure/chessknight.h \
    Figure/chessknight.h \
    Figure/chessrook.h \
    Figure/chessrook.h \
    Figure/figure.h \
    Figure/figure.h \
    Figure/prize.h \
    Figure/prize.h \
    StartWindow/startwindow.h \
    mainwindow.h \
    ratingboard.h

FORMS += \
    StartWindow/startwindow.ui \
    mainwindow.ui \
    ratingboard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resourse.qrc
