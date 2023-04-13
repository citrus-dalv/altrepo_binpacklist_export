#include <iostream>
#include <exception>
#include "altrepo_export.h"
#include "fileManager.h"

#define URL "https://rdb.altlinux.org/api/export/branch_binary_packages/"

int main()
{
    using namespace altrepo;
    Exporter exp(URL);
    PackageKit f_packs, s_packs;

    int f_cnt = exp.export_branch_packages("i586", "p10", f_packs);
    if (f_cnt == NONE) {
        std::cerr << exp.get_strerr() << std::endl;
        exp.~Exporter();
        exit(1);
    }

    int s_cnt = exp.export_branch_packages("i586", "p9f", s_packs);
    if (s_cnt == NONE) {
        std::cerr << exp.get_strerr() << std::endl;
        exp.~Exporter();
        exit(1);
    }

    std::cout << "first branch count: " << f_cnt << std::endl;
    std::cout << "second branch count: " << s_cnt << std::endl;

    return 0;
}
