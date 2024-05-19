QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    isbn_new_version.cpp \
    isbn_old_version.cpp \
    main.cpp \
    welcome_user.cpp

HEADERS += \
    isbn_new_version.h \
    isbn_old_version.h \
    welcome_user.h

FORMS += \
    isbn_new_version.ui \
    isbn_old_version.ui \
    welcome_user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
