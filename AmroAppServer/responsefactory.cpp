#include "responsefactory.h"

#include "clientresponse.h"
#include "materialresponse.h"
#include "userresponse.h"
#include "certificateresponse.h"

Response* ResponseFactory::CreateResponse(QString target)
{
    if (target == "User")
        return new UserResponse();
    else if (target == "Client")
        return new ClientResponse();
    else if (target == "Material")
        return new MaterialResponse();
    else if (target == "Certificate")
        return new CertificateResponse();
    else
        return NULL;
}
