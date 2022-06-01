TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c

unix:!macx|win32: LIBS += D:/qt/hid_c_tst/lib/libusb-1.0.a

INCLUDEPATH += D:/qt/hid_c_tst/inc/
DEPENDPATH += D:/qt/hid_c_tst/inc/
