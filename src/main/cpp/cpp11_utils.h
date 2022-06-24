// fan_string.hpp
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <vector>
#include <string>

namespace fan
{
    bool startswith(const std::string &str, const std::string &prefix)
    {
        return str.rfind(prefix) == 0;
    }

    bool endswith(const std::string &str, const std::string &suffix)
    {
        if (suffix.size() > str.size())
            return false;
        return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
    }

    bool is_directory(const std::string &path)
    {
        struct stat sb;
        stat(path.c_str(), &sb);
        return S_IFDIR == (sb.st_mode & S_IFMT);
    }

    bool is_regular_file(const std::string &path)
    {
        struct stat sb;
        stat(path.c_str(), &sb);
        return S_IFREG == (sb.st_mode & S_IFMT);
    }

    std::vector<std::string> directory_filenames(const std::string &path)
    {
        std::vector<std::string> filenames;
        if (is_directory(path))
        {
            DIR *dir;
            dir = opendir(path.c_str());
            if (dir)
            {
                struct dirent *entry;
                while (entry = readdir(dir))
                {
                    if (endswith(path, "/"))
                        filenames.push_back(path + entry->d_name);
                    else
                        filenames.push_back(path + "/" + entry->d_name);
                }

                closedir(dir);
            }
        }
        return filenames;
    }

}