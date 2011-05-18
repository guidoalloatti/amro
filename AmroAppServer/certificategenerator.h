#ifndef CERTIFICATEGENERATOR_H
#define CERTIFICATEGENERATOR_H

#include "../DataLibrary/certificate.h"

class CertificateGenerator
{
public:
    CertificateGenerator();

    bool generate(Certificate &c);
};

#endif // CERTIFICATEGENERATOR_H
