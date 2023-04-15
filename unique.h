/* unique.h */
#pragma once
#include "lib/include/altrepo_export.h"

    /* Macrofunctions to get access to result JSON fields */
#define BRANCH_NAME(json,arg)  json["uniques"][#arg]["name"]
#define BRANCH_PACKAGES(json,arg) json["uniques"][#arg]["packages"]
#define PACKAGES_COUNT(json,arg) json["uniques"][#arg]["count"]

    /* Macrofunctions to work with source JSON */
#define PACKAGES_BEGIN(json) json["packages"].begin()
#define PACKAGES_END(json) json["packages"].end()

using namespace altrepo;

void show_unique(const PackageKit &first, const PackageKit &second);
