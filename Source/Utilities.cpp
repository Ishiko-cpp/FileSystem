/*
    Copyright (c) 2017-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#include "Utilities.h"
#include "ErrorCategory.h"
#include <boost/filesystem/operations.hpp>
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
#include <windows.h>
#endif
#include <fstream>

namespace Ishiko
{
namespace FileSystem
{

bool Exists(const char* path)
{
    return boost::filesystem::exists(path);
}

bool Exists(const std::string& path)
{
    return Exists(path.c_str());
}

bool Exists(const boost::filesystem::path& path)
{
    return Exists(path.string());
}

size_t GetFileSize(const char* path)
{
    return boost::filesystem::file_size(path);
}

bool IsDirectory(const char* path, Error& error)
{
    try
    {
        if (Exists(path))
        {
            return boost::filesystem::is_directory(path);
        }
        else
        {
            Fail(error, ErrorCategory::eNotFound);
            return false;
        }
    }
    catch (...)
    {
        // According to the Boost documentation boost::filesystem::is_directory throws when the path doesn't exist but
        // it doesn't seem to do that in our tests.
        Fail(error, ErrorCategory::eNotFound);
        return false;
    }
}

bool IsEmpty(const char* path, Error& error)
{
    try
    {
        return boost::filesystem::is_empty(path);
    }
    catch (...)
    {
        Fail(error, ErrorCategory::eNotFound);
        return false;
    }
}

void ToAbsolutePath(const char* path, std::string& absolutePath)
{
    absolutePath = boost::filesystem::absolute(path).string();
}

void ToAbsolutePath(const std::string& path, std::string& absolutePath)
{
    absolutePath = boost::filesystem::absolute(path).string();
}

void CreateEmptyFile(const std::string& path, Error& error)
{
    // TODO: use lower level file functions to make this more robust
    if (!Exists(path))
    {
        std::ofstream file(path);
    }
    else
    {
        Fail(error, ErrorCategory::eAlreadyExists);
    }
}

void CreateEmptyFile(const boost::filesystem::path& path, Error& error)
{
    CreateEmptyFile(path.string(), error);
}

size_t ReadFile(const char* filename, char* buffer, size_t bufferSize, Error& error)
{
    size_t result = 0;

    try
    {
        size_t filesize = boost::filesystem::file_size(filename);
        if (filesize <= bufferSize)
        {
            FILE* file = fopen(filename, "rb");
            if (file)
            {
                result = fread(buffer, 1, filesize, file);
                fclose(file);
            }
        }
        else
        {
            result = filesize;
            Fail(error, ErrorCategory::eBufferOverflow);
        }
    }
    catch (...)
    {
        Fail(error, ErrorCategory::eGeneric);
    }

    return result;
}

#if ISHIKO_OS == ISHIKO_OS_WINDOWS
void GetVolumeList(std::vector<std::string>& volumeNames, Error& error)
{
    char volumeName[MAX_PATH + 1];
    HANDLE searchHandle = FindFirstVolumeA(volumeName, MAX_PATH + 1);
    if (searchHandle == INVALID_HANDLE_VALUE)
    {
        Fail(error, ErrorCategory::eGeneric);
    }
    else
    {
        volumeNames.emplace_back(volumeName);
        while (FindNextVolumeA(searchHandle, volumeName, MAX_PATH + 1))
        {
            volumeNames.emplace_back(volumeName);
        }
        FindVolumeClose(searchHandle);
    }
}
#endif

}
}
