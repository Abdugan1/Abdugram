#ifndef ABDUMESSAGEFACTORY_H
#define ABDUMESSAGEFACTORY_H

#include "abdumessage.h"

class AbduMessageFactory
{
public:
    static AbduMessagePtr fromData(const QByteArray &data);
};

#endif // ABDUMESSAGEFACTORY_H
