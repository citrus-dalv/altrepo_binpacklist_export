/* fileManager.h */
#pragma once

#include <cstdio>
#include <string>
#include <string_view>
#include <cstring>
#include <fstream>
#include <map>
#include <cerrno>
#include <unistd.h>
#include "iface.h"

namespace altrepo {
                /* FileManager takes responsibility for work with files */
class FileManager : public IFace
{
public:
    FileManager();
    ~FileManager();

    FILE* open(const char*, const char*, FILE* = nullptr);
    const char* get_strerr() const override;
    void close(const char*);
    void close_all();
    void delete_all();
private:
    std::string error;
    std::map<std::string, FILE*> opened_files;
};

}
