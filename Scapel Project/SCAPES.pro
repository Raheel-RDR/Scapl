#-------------------------------------------------
#
# Project created by QtCreator 2019-11-05T15:14:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = textEditor
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
        mainwindow.cpp \
        operand/cmp.cpp \
        operand/add.cpp \
        operand/mov.cpp \
        operand/declareInteger.cpp \
        operand/declareIntegerArray.cpp \
        operand/jmp.cpp \
        operand/jmr.cpp \
        operand/jls.cpp \
        operand/jeq.cpp\
        operand/operand.cpp \
        operand/printVariable.cpp \
        operand/readVariable.cpp \
        program/program.cpp \
        rundialog.cpp \
        serializer/serializer.cpp

HEADERS += \
        mainwindow.h \
        operand/cmp.h \
        operand/add.h \
        operand/mov.h \
        operand/comment.h \
        operand/declareInteger.h \
        operand/declareIntegerArray.h \
        operand/end.h \
        operand/jmp.h \
        operand/jmr.h \
        operand/jls.h \
        operand/jeq.h \
        operand/operand.h \
        operand/printVariable.h \
        operand/readVariable.h \
        program/program.h \
        variable/integerVariable.h \
        variable/integerArrayVariable.h \
        variable/literalInteger.h \
        variable/literalText.h \
        variable/variable.h \
        variable/integerArrayVariableWithLiteralIndex.h\
        variable/integerArrayVariableWithVariableIndex.h\
        rundialog.h \
        serializer/serializer.h

FORMS += \
        mainwindow.ui \
        rundialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
