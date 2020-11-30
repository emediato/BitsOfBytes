//If you don’t want to use the project wizard, you need to add testlib to the QT variable in your qmake project file:
QT += testlib

//If your unit test does not involve any GUI elements, it is possible to disable the gui module:
QT -= gui



CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    TestCalculator.cpp

HEADERS += \
    Calculator.h \
    TestCalculator.h
