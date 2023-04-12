/* curlManager.cpp */
#include "../include/curlManager.h"
using namespace curl;

CurlManager::CurlManager() = default;
CurlManager::~CurlManager()
{
    uninit();
}

CurlManager::CurlManager(const CurlManager &other) = delete;
CurlManager::CurlManager(CurlManager &&other)      = delete;
CurlManager& CurlManager::operator=(const CurlManager& other) = delete;
CurlManager& CurlManager::operator=(CurlManager&& other)      = delete;

bool CurlManager::init()
{
    if (initStatus) {
        error = "initialized already or other instance works";
        return false;
    }
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl)
        error = "can't initialize library";
    else
        initStatus = true;
    return initStatus;
}

void CurlManager::uninit()
{
    if (!initStatus)
        return;
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    curl = nullptr;
    initStatus = false;
}

CurlManager::operator bool() const { return initStatus; }

bool CurlManager::get_data(const char *url, FILE *out)
{
    if (!initStatus) {
        error = "not initialized";
        return false;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, out);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        error = "response fail: ";
        error += url_easy_strerror(res) << std::endl;
        return false;
    }
    return true;
}
