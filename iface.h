/* iface.h */
#pragma once

class IFace
{
public:
    virtual const char* get_strerr() const = 0;
};
