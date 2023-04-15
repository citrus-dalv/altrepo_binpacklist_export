/* res_struct.h */
#pragma once

                    /* Macrofunctions to get access to result JSON fields */
#define BRANCH_NAME(json,arg)  json["uniques"][#arg]["name"]
#define BRANCH_PACKAGES(json,arg) json["uniques"][#arg]["packages"]
#define PACKAGES_COUNT(json,arg) json["uniques"][#arg]["count"]

                   /* Macrofunctions to work with source JSON */
#define PACKAGES_BEGIN(json) json["packages"].begin()
#define PACKAGES_END(json) json["packages"].end()

                   /* JSON result structure */
static const char *json_res_struct =
                "{\"arch\": null, \
                  \"uniques\": \
                       {\"first\":\
                           {\
                               \"name\" : null,\
                               \"count\": null, \
                               \"packages\" : []\
                           }, \
                          \"second\":\
                               {\
                                \"name\" : null,\
                                \"count\": null, \
                                \"packages\" : []\
                               }\
                       },\
                   \"upper_version\":\
                        {\
                          \"count\": null,\
                          \"packages\":[]\
                        }\
                 }";
