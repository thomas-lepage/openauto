QT       += core gui

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
INCLUDEPATH += ../../../include/

SOURCES += \
    ConnectDialog.cpp \
    MusicWindow.cpp \
    SettingsWindow.cpp \
    MainWindow.cpp \

HEADERS += \
    ../../../include/f1x/openauto/autoapp/UI/MainWindow.hpp \
    ../../../include/f1x/openauto/autoapp/UI/ConnectDialog.hpp \
    ../../../include/f1x/openauto/autoapp/UI/MusicWindow.hpp \
    ../../../include/f1x/openauto/autoapp/UI/SettingsWindow.hpp \

FORMS += \
    mainwindow.ui \
    connectdialog.ui \
    musicwindow.ui \
    settingswindow.ui \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../aasdk/lib/release/ -laasdk
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../aasdk/lib/debug/ -laasdk
else:unix: LIBS += -L$$PWD/../../../../aasdk/lib/ -laasdk

INCLUDEPATH += $$PWD/../../../../aasdk/include
DEPENDPATH += $$PWD/../../../../aasdk/include

RESOURCES += \
    ../../../assets/resources.qrc
