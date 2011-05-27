#-------------------------------------------------
#
# Project created by QtCreator 2011-03-18T12:13:13
#
#-------------------------------------------------

QT += sql
QT += gui
TARGET = DataLibrary
TEMPLATE = lib
DEFINES += DATALIB_LIBRARY

SOURCES += main.cpp \
    datalib.cpp \
    database.cpp \
    query.cpp \
    user.cpp \
    privilege.cpp \
    client.cpp \
    certificate.cpp \
    material.cpp \
    chemicalmeasure.cpp \
    mechanicalmeasure.cpp \
    usermapper.cpp \
    clientmapper.cpp \
    materialmapper.cpp \
    certificatemapper.cpp \
    privilegemapper.cpp \
    userpermissionsmapper.cpp \
    clientcodemapper.cpp \
    csvparsingline.cpp \
    csvparsinglinemapper.cpp \
    chemicalanalysis.cpp \
    chemicalanalysismapper.cpp \
    mechanicalanalysis.cpp \
    mechanicalanalysismapper.cpp \
    termicaltreatment.cpp \
    termicaltreatmentmapper.cpp

HEADERS += \
    datalib.h \
    database.h \
    query.h \
    DataLib_global.h \
    user.h \
    privilege.h \
    client.h \
    certificate.h \
    material.h \
    chemicalmeasure.h \
    mechanicalmeasure.h \
    usermapper.h \
    clientmapper.h \
    materialmapper.h \
    certificatemapper.h \
    privilegemapper.h \
    userpermissionsmapper.h \
    clientcodemapper.h \
    csvparsingline.h \
    csvparsinglinemapper.h \
    chemicalanalysis.h \
    chemicalanalysismapper.h \
    mechanicalanalysis.h \
    mechanicalanalysismapper.h \
    termicaltreatment.h \
    termicaltreatmentmapper.h
