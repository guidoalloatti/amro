#include "responsefactory.h"

#include "clientresponse.h"
#include "materialresponse.h"
#include "userresponse.h"
#include "certificateresponse.h"
#include "analysisresponse.h"
#include "csvparsingresponse.h"


Response* ResponseFactory::createResponse(QString target)
{
    if (target == "User")
        return new UserResponse();
    else if (target == "Client")
        return new ClientResponse();
    else if (target == "Material")
        return new MaterialResponse();
    else if (target == "Certificate")
        return new CertificateResponse();
    else if (target == "CSVParsing")
        return new CSVParsingResponse();
    else if (target == "Analysis")
        return new AnalysisResponse();
    else
        return NULL;
}
