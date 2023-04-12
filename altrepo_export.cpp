/* altrepo_export.cpp */

#include "altrepo_export.h"
#include "curlManager.h"

using namespace altrepo;

Exporter::Exporter()  = default;
Exporter::Exporter(const char *url) : url_export{url} {}
Exporter::~Exporter() = default;

const char* Exporter::get_strerr() const { return error.data(); }

int Exporter::export_branch_packages(const char *arch, const char *branch,
                                     PackageKit &packs)
{
    if (!*arch || !*branch) { error = "empty parameter"; return ERROR; }
    if (!url_export.length()) { error = "url empty"; return ERROR; }

    std::string url = exp_pack_url(arch, branch);      /* Url making */
    std::string filename = exp_filename(arch, branch); /* Filename making */

    FILE *fout = fopen(filename.data(), "w"); /* Temporary file creating */
    if (!fout) {
        error = "can't open temporary file";
        return ERROR;
    }
    curl::CurlManager cm;                     /* Start work with curl */
    if (!cm.init()) { error = "can't init curlManager"; return ERROR; }
    if (!cm.get_data(url.data(), fout)) {     /* Try to retrieve data */
        error = "can't get data: "; error += cm.get_strerr();
        unlink(filename.data());              /* Temporary file deleting */
        return ERROR;
    }
    /* File size can be huge, but we need to reopen it for read. We have
     * to be sure then all output operations to files been done. */
    sync();
    fclose(fout);

    /* Reopening file to make json type from file data */
    std::ifstream fin; fin.open(filename);
    if (!fin.is_open()) {
        error = "can't reopen temporary file to read";
        unlink(filename.data());
        return ERROR;
    }
    
    fin >> packs.js;  /* Making of json object from file data */
    if (!resp_handler(packs.js)) {
        unlink(filename.data());
        return ERROR;
    }

    packs.count  = packs.js["length"];
    packs.arch   = arch;
    packs.branch = branch;
    fin.close();
    unlink(filename.data());   /* Temporary file deleting */
    error.clear();
    return packs.count;
}

void Exporter::set_url_export(const char* url) { url_export = url; }

bool Exporter::resp_handler(const nlohmann::json &j)
{
    if (j.contains("message")) {
        error = j["message"];
        if (j.contains("validation_message"))
                std::cerr << j["validation_message"][0] << std::endl;
        if (j.contains("errors"))
                std::cerr << j["errors"]["arch"] << std::endl;
        return false;
    }
    return true;
}

std::string Exporter::exp_pack_url(const char *arch, const char *br) const
{
    if (!*arch || !*br) return "";
    std::string result;
    result = url_export; result += br; result += "?arch="; result += arch;
    return result;
}

std::string Exporter::exp_filename(const char *arch, const char *br) const
{
    if (!*arch || !*br) return "";
    std::string result = br; result += '_'; result += arch;
    return result;
}
