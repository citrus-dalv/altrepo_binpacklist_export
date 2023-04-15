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
#include "json.h"

namespace altrepo {
                /* FileManager takes responsibility for work with files.
                 * When class instance is destroyed, it tries to delete
                 * all created files. */
class FileManager : public IFace
{
public:
    FileManager();
    ~FileManager();
                /* Opens file with required mode */
    FILE* open(const char*, const char*, FILE* = nullptr);
                /* Closes file, filename required */
    void close(const char*);
                /* Closes all files */
    void close_all();
                /* Tries to close and delete all created files */
    void delete_all();
                /* Parsing from file to JSON */
    bool parse_to_json(const std::string&, nlohmann::json&);
                /* Returns error message of last job */
    const char* get_strerr() const override;
private:
    std::string error;
    std::map<std::string, FILE*> opened_files;
};

}
