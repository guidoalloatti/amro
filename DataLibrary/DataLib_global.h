#ifndef DATALIB_GLOBAL_H
#define DATALIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DATALIB_LIBRARY)
#  define DATALIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DATALIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DATALIB_GLOBAL_H
