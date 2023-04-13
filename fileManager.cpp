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
        error.clear();
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
    error.clear();
}

void FileManager::close_all()
{
    for (auto f : opened_files) {
        fclose(f.second);
        f.second = nullptr;
    }
    error.clear();
}

void FileManager::delete_all()
{
    for (auto f : opened_files) {
        if (f.second)
            fclose(f.second);
        unlink(f.first.data());
    }
    opened_files.clear();
    error.clear();
}

bool FileManager::parse_to_json(const std::string &filename,
                                nlohmann::json &j)
{
    bool wasOpened = false; /* If file was opened, will open again at end */
    auto f = opened_files.find(filename);
    if (f != opened_files.end())
        if (f->second) wasOpened = true;

    /* We have to call sync() because if file was opened, we need to
     * reopen it to make ifstream object for parsing. We have to be sure
     * than all operations with files has been done */
    sync();
    close(filename.data());
    std::ifstream fin(filename);
    if (fin) {
        fin >> j; fin.close();
        error.clear();
    } else {
        error = "can't open file "; error += filename;
        error += std::strerror(errno);
        return false;
    }
    if (wasOpened) f->second = open(filename.data(), "w");

    return true;
}

const char* FileManager::get_strerr() const
{
    return error.data();
}
