#include <iostream>
#include <exception>
#include <altrepo/altrepo_export.h>
#include "unique.h"

#define DEFURL "https://rdb.altlinux.org/api/export/branch_binary_packages/"

int main(int argc, char **argv)
{
    if (argc != 4) {
        std::cerr << "expects three command line args: " <<
            "{arch} {branch one} {branch two}" << std::endl;
        exit(1);
    }
    /* Tries to export packages to structures f_packs, s_packs from server,
     * and if success, call function show_unique, that output result
     * like JSON */

    using namespace altrepo;
    try {
        Exporter exp(DEFURL);
        PackageKit f_packs, s_packs;

        int f_cnt = exp.export_branch_packages(argv[1], argv[2], f_packs);
        if (f_cnt == NONE) { /* If not retrieved any packages */
            std::cerr << exp.get_strerr() << std::endl;
            exp.~Exporter(); /* Desctructor call befor exit */
            exit(1);
        }

        int s_cnt = exp.export_branch_packages(argv[1], argv[3], s_packs);
        if (s_cnt == NONE) {
            std::cerr << exp.get_strerr() << std::endl;
            exp.~Exporter();
            exit(1);
        }

        show_unique(f_packs, s_packs);
    }
    catch (std::exception &ex) { std::cerr << ex.what() << std::endl; }
    catch (const char *msg) { std::cerr << msg << std::endl; }
    catch (...) { std::cerr << "undefined exception" << std::endl; }

    return 0;
}
