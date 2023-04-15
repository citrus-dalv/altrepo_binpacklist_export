/* altrepo_export.cpp */

#include "../include/altrepo_export.h"
#include "../include/curlManager.h"

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

    CurlManager cm;          /* Start work with curl */
    if (!cm.init()) { error = "can't init curlManager"; return ERROR; }
                             /* Try to retrieve data */
    if (!cm.get_data(url.data(), fm.open(filename.data(), "w"))) {
        error = "can't get data: "; error += cm.get_strerr();
        return ERROR;
    }
                             /* Parsing from file to JSON */
    if (!fm.parse_to_json(filename, packs.js)) {
        error = "can't make parsing from file to JSON: ";
        error += fm.get_strerr();
        return ERROR;
    }
    if (!resp_handler(packs.js)) return ERROR;

    packs.count  = packs.js["length"];
    packs.arch   = arch;
    packs.branch = branch;
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
    if (!j.contains("length")) {
        error = "JSON structure invalid";
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

std::string Exporter::exp_filename(const char *arch, const char *br)
{
    if (!*arch || !*br) return "";
    std::string result = br; result += '_'; result += arch;
    return result;
}
