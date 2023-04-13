/* fileManager.cpp */
#include "fileManager.h"

using namespace altrepo;

FileManager::FileManager() = default;
FileManager::~FileManager()
{
    delete_all();
}

FILE* FileManager::open(const char *name, const char *mode, FILE *f)
{
    FILE* file = fopen(name, mode);
    if (file) {
        opened_files[name] = file;
        if (f) f = file;
        return file;
    } else {
        error = std::strerror(errno);
        return nullptr;
    }
}

void FileManager::close(const char *name)
{
    auto found = opened_files.find(name);
    if (found != opened_files.end()) {
        fclose(found->second);
        found->second = nullptr;
    }
}

void FileManager::close_all()
{
    for (auto f : opened_files) {
        fclose(f.second);
        f.second = nullptr;
    }
}

void FileManager::delete_all()
{
    for (auto f : opened_files) {
        if (f.second)
            fclose(f.second);
        unlink(f.first.data());
    }
    opened_files.clear();
}

const char* FileManager::get_strerr() const
{
    return error.data();
}
