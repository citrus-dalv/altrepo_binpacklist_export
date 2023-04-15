/* showUnique.cpp */
#include "unique.h"

using namespace altrepo;

static const char *result_struct_json =
R"(
    {
        "arch": null,
        "uniques":
            {
                "first":{"name" : null, "count": null, "packages" : []},
                "second":{"name" : null, "count": null, "packages" : []}
            },
        "upper_version":
            {
                "count": null,
                "packages":[]
            }
    }
)";

void static unique_algorithm(nlohmann::json &j, const PackageKit &f,
                             const PackageKit &s)
{
    j["arch"] = f.arch; /* Copies information to result */
    BRANCH_NAME(j,first) = f.branch; BRANCH_NAME(j,second) = s.branch;
                        /* Iterators to source JSON packages begin */
    auto f_it = PACKAGES_BEGIN(f.js); auto s_it = PACKAGES_BEGIN(s.js);
                        /* Detected packages count */
    int f_cnt{}, s_cnt{}, av_cnt{}; 
    
    /* The algorithm has linear complexity. Consistently compares package
     * names in both structures. Packages are provided in alphabetical
     * order. If the compared packages are not equal, then the one whose
     * name is less is added to the corresponding result array. If the
     * names are equal and the version of the package in the first branch
     * is less than the package in the second branch, then it is added to
     * the upper_version array of the result.
    */
    while (f_it != PACKAGES_END(f.js) && s_it != PACKAGES_END(s.js)) {
        if (f_it.value()["name"] < s_it.value()["name"]) {
            j["uniques"]["first"]["packages"].push_back(f_it.value()); 
            f_cnt++; f_it++;
        } else if (s_it.value()["name"] < f_it.value()["name"]) {
            j["uniques"]["second"]["packages"].push_back(s_it.value()); 
            s_cnt++; s_it++;
        } else {
            if (f_it.value()["version"] > s_it.value()["version"])
                j["upper_version"]["packages"].push_back(f_it.value());
            av_cnt++; f_it++; s_it++;
        }
    }
                /* Adds remaining packages */ 
    while (f_it != PACKAGES_END(f.js)) {
        BRANCH_PACKAGES(j,first).push_back(f_it.value()); 
        f_cnt++;
    }
    while (s_it != PACKAGES_END(s.js)) {
        BRANCH_PACKAGES(j,second).push_back(s_it.value()); 
        s_cnt++;
    }
                /* Writes detected packages counts */
    PACKAGES_COUNT(j,first) = f_cnt; PACKAGES_COUNT(j,second) = s_cnt;
    j["upper_version"]["count"] = av_cnt;
}

void show_unique(const PackageKit &f, const PackageKit &s)
{
    if (f.arch != s.arch) {
        std::cerr << "given packages of different architectures";
        return;
    } else if (f.branch == s.branch) {
        std::cerr << "given the same branches";
        return;
    }

    nlohmann::json result = nlohmann::json::parse(result_struct_json);
    unique_algorithm(result, f, s);

    std::cout << std::setw(4) << result << std::endl;
}
