/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_DIRECTORY_H_
#define _ISHIKO_CPP_FILESYSTEM_DIRECTORY_H_

#include <functional>
#include <string>

namespace Ishiko
{
namespace FileSystem
{

class Directory
{
public:
    Directory(const char* path);

    void forEachRegularFile(std::function<void(const std::string& path)> callback, bool recursive);

private:
    std::string m_path;
};

}
}

#endif
