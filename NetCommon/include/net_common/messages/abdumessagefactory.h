#ifndef ABDUMESSAGEFACTORY_H
#define ABDUMESSAGEFACTORY_H

#include "abdumessage.h"

class NETCOMMON_EXPORT AbduMessageFactory
{
public:
    static AbduMessagePtr fromData(const QByteArray &data);
};

#endif // ABDUMESSAGEFACTORY_H
