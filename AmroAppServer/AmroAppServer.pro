#-------------------------------------------------
#
# Project created by QtCreator 2011-03-21T17:05:20
#
#-------------------------------------------------

QT       += core
QT       += gui
QT       += webkit


TARGET = AmroAppServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
QT += network
QT += sql



SOURCES += main.cpp \
    requestlistener.cpp \
    requesthandler.cpp \
    jsonp.cpp \
    responsemapper.cpp \
    response.cpp \
    responsefactory.cpp \
    clientresponse.cpp \
    userresponse.cpp \
    materialresponse.cpp \
    certificateresponse.cpp \
    csvparsingresponse.cpp \
    analysisresponse.cpp \
    certificategenerator.cpp \
    certificateprinter.cpp \
    cprinter.cpp \
    termicaltreatmentresponse.cpp

HEADERS += \
    requestlistener.h \
    requesthandler.h \
    jsonp.h \
    responsemapper.h \
    response.h \
    responsefactory.h \
    clientresponse.h \
    userresponse.h \
    materialresponse.h \
    certificateresponse.h \
    csvparsingresponse.h \
    analysisresponse.h \
    certificategenerator.h \
    certificateprinter.h \
    cprinter.h \
    termicaltreatmentresponse.h

LIBS += -L../DataLibrary \
    -lDataLibrary
