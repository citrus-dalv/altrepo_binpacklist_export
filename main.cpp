#include <iostream>
#include <exception>
#include "altrepo_export.h"
#include "fileManager.h"
#include "showUnique.h"

#define URL "https://rdb.altlinux.org/api/export/branch_binary_packages/"

int main()
{
    using namespace altrepo;
    try {
        Exporter exp(URL);
        PackageKit f_packs, s_packs;

        int f_cnt = exp.export_branch_packages("i586", "p10", f_packs);
        if (f_cnt == NONE) {
            std::cerr << exp.get_strerr() << std::endl;
            exp.~Exporter();
            exit(1);
        }

        int s_cnt = exp.export_branch_packages("i586", "p9", s_packs);
        if (s_cnt == NONE) {
            std::cerr << exp.get_strerr() << std::endl;
            exp.~Exporter();
            exit(1);
        }

        std::cout << "first branch count: " << f_cnt << std::endl;
        std::cout << f_packs.js["length"] << std::endl;
        std::cout << "second branch count: " << s_cnt << std::endl;
    }
    catch (std::exception &ex) { std::cerr << ex.what() << std::endl; }
    catch (const char *msg) { std::cerr << msg << std::endl; }
    catch (...) { std::cerr << "undefined exception" << std::endl; }

    return 0;
}
