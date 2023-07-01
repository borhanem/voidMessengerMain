QT       += core gui
QT          +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractchat.cpp \
    api.cpp \
    channelchat.cpp \
    createchannelpage.cpp \
    creategrouppage.cpp \
    groupchat.cpp \
    loginpage.cpp \
    main.cpp \
    mainwindow.cpp \
    message.cpp \
    msgBaseReceive.cpp \
    msgBaseSend.cpp \
    refresherDirect.cpp \
    refresherabstract.cpp \
    refresherchannel.cpp \
    refresherchannellist.cpp \
    refresherdirectlist.cpp \
    refreshergroup.cpp \
    refreshergrouplist.cpp \
    registerpage.cpp \
    theme.cpp \
    user.cpp

HEADERS += \
    abstractchat.h \
    api.h \
    channelchat.h \
    createchannelpage.h \
    creategrouppage.h \
    groupchat.h \
    loginpage.h \
    mainwindow.h \
    message.h \
    msgBaseReceive.h \
    msgBaseSend.h \
    refresherDirect.h \
    refresherabstract.h \
    refresherchannel.h \
    refresherchannellist.h \
    refresherdirectlist.h \
    refreshergroup.h \
    refreshergrouplist.h \
    registerpage.h \
    theme.h \
    user.h

FORMS += \
    channelchat.ui \
    createchannelpage.ui \
    creategrouppage.ui \
    groupchat.ui \
    loginpage.ui \
    mainwindow.ui \
    msgBaseReceive.ui \
    msgBaseSend.ui \
    registerpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Styles.qrc
