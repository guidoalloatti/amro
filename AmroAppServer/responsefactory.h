#ifndef RESPONSEFACTORY_H
#define RESPONSEFACTORY_H

#include "response.h"

class ResponseFactory
{
public:
    ResponseFactory() {}

    Response* createResponse(QString target);
};

#endif // RESPONSEFACTORY_H
