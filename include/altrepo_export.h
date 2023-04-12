/* altrepo_export.h */
#pragma once

#include <string>
#include <fstream>
#include <unistd.h>

#include "curlManager.h"
#include "json.h"

#define DEFAULT_URL "https://rdb.altlinux.org/api/export/branch_binary_packages/"

namespace altrepo
{

enum errors {
    ERROR -1
}

struct PackageList           /* Struct to store result of packages export */
{
    std::string arch;        /* Arch name */
    std::string branch;      /* Branch name */
    int count = 0;           /* Packs count retrieved */
    nlohmann::json packs_js; /* Json view of data */
};

class Exporter               /* Class Exporter takes responsibility */
{                            /* of data retrieving from REST API */
public:
    Exporter();
    ~Exporter();
                             /* Function expects arch and branch names,
                                and struct to store result. Returns
                                number of retrieved packets */
    int export_branch_packages(const char*, const char*, PackageList&);

                             /* Returns error msg of last job */
    const char* getErrorMsg() const; 
private:
    std::string error;
};

}
