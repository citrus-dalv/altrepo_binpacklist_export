/* curlManager.h */
#pragma once

#include <curl/curl.h>
#include <iostream>

namespace curl {

class CurlManager
{
public:
    CurlManager();
    ~CurlManager();
    CurlManager(const CurlManager&);
    CurlManager(CurlManager&&);
    CurlManager& operator=(const CurlManager&);
    CurlManager& operator=(CurlManager&&);
    explicit operator bool() const;
    bool init();                     /* Init to work with curl library */
    void uninit();                   /* Uninit */

                                     /* Function retrieves data from url to
                                        stream */
    bool get_data(const char*, FILE* = stdout);

    const char* getErrorMsg() const; /* Returns error message of last job */
private:
    std::string error;               /* Error message */

    static inline bool initStatus{}; /* Shows library initialization status.
                                        Does not allow you to create more
                                        than one instance of class. */

    CURL *curl = nullptr;            /* Curl requirements */
    CURLcode res;
};

}
