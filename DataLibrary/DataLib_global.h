#ifndef DATALIB_GLOBAL_H
#define DATALIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(Q_WS_WIN)
    #if defined(DATALIB_LIBRARY)
        #  define DATALIBSHARED_EXPORT __declspec(dllexport)
    #else
        #  define DATALIBSHARED_EXPORT __declspec(dllimport)
    #endif
#else
    #if defined(DATALIB_LIBRARY)
        #  define DATALIBSHARED_EXPORT Q_DECL_EXPORT
    #else
        #  define DATALIBSHARED_EXPORT Q_DECL_IMPORT
    #endif
#endif

#endif // DATALIB_GLOBAL_H
