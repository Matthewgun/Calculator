QT       += core gui widgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Calculator.cpp \
    EngineeringCalculator.cpp \
    all_tests.cpp \
    converter.cpp \
    main.cpp \


HEADERS += \
    Calculator.h \
    EngineeringCalculator.h \
    all_tests.h \
    converter.h

FORMS += \
    Calculator.ui \
    EngineeringCalculator.ui \
    converter.ui

CONFIG += depend_includepath
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
DESTDIR = $$OUT_PWD
