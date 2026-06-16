QT       += widgets core

TEMPLATE = app
TARGET   = ChessAi

SOURCES += Code/*.cc
HEADERS += Header/*.hh

FORMS   += chess.ui

RESOURCES += resources.qrc

LIBS += -lcurl