/* altrepo_export.h */
#pragma once

#include <string>
#include <fstream>
#include <unistd.h>

#include "curlManager.h"
#include "json.h"

namespace altrepo
{

enum errors {
    ERROR = -1,
    EMPTY = -1
};

struct PackageKit            /* Struct to store result of packages export */
{
    std::string arch;        /* Arch name */
    std::string branch;      /* Branch name */
    int count = 0;           /* Packs count retrieved */
    nlohmann::json js;       /* Json view of data */
};

class Exporter               /* Class Exporter takes responsibility */
{                            /* of data retrieving from REST API */
public:
    Exporter();
    Exporter(const char*);
    ~Exporter();
                             /* Function expects arch and branch names,
                                and struct to store result. Returns
                                number of retrieved packets */
    int export_branch_packages(const char*, const char*, PackageKit&);

                             /* Returns error msg of last job */
    void set_url_export(const char*);
    const char* get_strerr() const; 
private:
    std::string error;       /* Last failure job message */
    std::string url_export;  /* Contains basic url for GET export queries */

                             /* Help functions */
                             /* Check for errors in response */
    bool resp_handler(const nlohmann::json&);
                             /* Making of export branch packets url */
    std::string exp_pack_url(const char*, const char*) const;
                             /* Making of filename for export packets */
    std::string exp_filename(const char*, const char*) const;
};

}
