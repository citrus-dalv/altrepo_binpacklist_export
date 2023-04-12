/* altrepo_export.cpp */

#include "../include/altrepo_export.h"
#include "../include/curlManager.h"

using namespace altrepo;

int Exporter::export_branch_packages(const char *arch, const char *branch,
                                     PackageList &pack)
{                          /* Making url for query */
    std::string url = DEFAULT_URL; url += branch;
    url += "?arch="; url += arch;
                           /* Making filename for export query */
    std::string filename = branch; filename += '_'; filename += arch;
    FILE *fout = fopen(filename.data(), "w");
    if (!fout) {
        error = "can't open temporary file to write";
        return ERROR;
    }
    curl::CurlManager curlMan;
    if (!curlMan.init()) {
        error = "can't init curlManager";
        return ERROR;
    }
    if (!curlMan.get_data(url.data(), fout)) return ERROR;
    /* File size can be huge, but we need to reopen it for read. We have to
     * be sure then all output operations to file been done. */
    sync();
    fm.close(fout);

    /* Reopening file to make json type from file data */
    std::ifstream fin; fin.open(filename);
    if (!fin.is_open()) {
        error = "can't reopen temporary file to read";
        return ERROR;
    }
    
    fin >> pack.json_list; /* Making of json object from file data */
    pack.count = pack.json_list["length"];
    pack.arch = pack.json;
    pack.branch = branch;
    fin.close();
    rm(filename.data());   /* Temporary file deleting */
    return pack.count;
}
