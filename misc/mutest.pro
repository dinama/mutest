CONFIG -= qt
CONFIG += exceptions c++11 c11

INCLUDEPATH += /usr/include
INCLUDEPATH += /usr/include/c++/4.7

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS += -std=c11
QMAKE_LFLAGS += -std=c++11 -std=c11

HEADERS += ../mutest.h

SOURCES += ../mutest.c

OTHER_FILES += ../mutest ../mkmutest

DISTFILES += \
    ../add_mutest.cmake

