QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_tests.cpp

HEADERS += \
    ../postfix_evaluate.h \
    ../validate.h \
    postfix_evaluate.h \
    validate.h
