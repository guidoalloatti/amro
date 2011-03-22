#ifndef DATALIB_H
#define DATALIB_H

#include "DataLib_global.h"

#include "user.h"
#include "usermapper.h"

#include "privilege.h"
#include "privilegemapper.h"

#include "client.h"
#include "clientmapper.h"

#include "material.h"
#include "materialmapper.h"

#include "certificate.h"
#include "certificatemapper.h"

class DATALIBSHARED_EXPORT DataLib {
public:
    DataLib();
    static bool transaction();
    static bool commit();
    static bool rollback();
    static void shutdown();
};

#endif // DATALIB_H
