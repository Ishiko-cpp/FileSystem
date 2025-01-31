// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "DirectoryTests.hpp"
#include <Ishiko/FileSystem/Directory.hpp>
#include <algorithm>

using namespace Ishiko;

DirectoryTests::DirectoryTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Directory tests", context)
{
    append<HeapAllocationErrorsTest>("constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 1", ForEachRegularFileTest1);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 2", ForEachRegularFileTest2);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 3", ForEachRegularFileTest3);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 4", ForEachRegularFileTest4);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 5", ForEachRegularFileTest5);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 6", ForEachRegularFileTest6);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 7", ForEachRegularFileTest7);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 8", ForEachRegularFileTest8);
    append<HeapAllocationErrorsTest>("getRegularFilesCount test 1", GetRegularFilesCountTest1);
    append<HeapAllocationErrorsTest>("getRegularFilesCount test 2", GetRegularFilesCountTest2);
    append<HeapAllocationErrorsTest>("getRegularFilesCount test 3", GetRegularFilesCountTest3);
}

void DirectoryTests::ConstructorTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("Directory1");

    Directory directory(inputPath);

    ISHIKO_TEST_PASS();
}

void DirectoryTests::ForEachRegularFileTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("Directory1");

    Directory directory(inputPath);

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const boost::filesystem::path& path)
        {
            files.emplace_back(path.generic_string());
        },
        false
    );

    ISHIKO_TEST_ABORT_IF_NEQ(files.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(files[0], "../../data/Directory1/file1.txt");
    ISHIKO_TEST_PASS();
}

void DirectoryTests::ForEachRegularFileTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("Directory2");

    Directory directory(inputPath);

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const boost::filesystem::path& path)
        {
            files.emplace_back(path.generic_string());
        },
        false
    );
    std::sort(files.begin(), files.end());

    ISHIKO_TEST_ABORT_IF_NEQ(files.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(files[0], "../../data/Directory2/file1.txt");
    ISHIKO_TEST_FAIL_IF_NEQ(files[1], "../../data/Directory2/file2.txt");
    ISHIKO_TEST_PASS();
}

void DirectoryTests::ForEachRegularFileTest3(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataDirectory() / "Directory3");

    Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const boost::filesystem::path& path)
        {
            files.emplace_back(path.generic_string());
        },
        false
    );

    ISHIKO_TEST_FAIL_IF_NEQ(files.size(), 0);
    ISHIKO_TEST_PASS();
}

void DirectoryTests::ForEachRegularFileTest4(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataDirectory() / "Directory4");

    Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const boost::filesystem::path& path)
        {
            files.emplace_back(path.generic_string());
        },
        false
        );

    ISHIKO_TEST_ABORT_IF_NEQ(files.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(files[0], "../../data/Directory4/file_1.txt");
    ISHIKO_TEST_PASS();
}

void DirectoryTests::ForEachRegularFileTest5(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataDirectory() / "Directory1");

    Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const boost::filesystem::path& path)
        {
            files.emplace_back(path.generic_string());
        },
        true
    );

    ISHIKO_TEST_ABORT_IF_NEQ(files.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(files[0], "../../data/Directory1/file1.txt");
    ISHIKO_TEST_PASS();
}

void DirectoryTests::ForEachRegularFileTest6(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataDirectory() / "Directory2");

    Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const boost::filesystem::path& path)
        {
            files.emplace_back(path.generic_string());
        },
        true
    );
    std::sort(files.begin(), files.end());

    ISHIKO_TEST_ABORT_IF_NEQ(files.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(files[0], "../../data/Directory2/file1.txt");
    ISHIKO_TEST_FAIL_IF_NEQ(files[1], "../../data/Directory2/file2.txt");
    ISHIKO_TEST_PASS();
}

void DirectoryTests::ForEachRegularFileTest7(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataDirectory() / "Directory3");

    Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const boost::filesystem::path& path)
        {
            files.emplace_back(path.generic_string());
        },
        true
    );

    ISHIKO_TEST_ABORT_IF_NEQ(files.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(files[0], "../../data/Directory3/dir_1/file_1_1.txt");
    ISHIKO_TEST_PASS();
}

void DirectoryTests::ForEachRegularFileTest8(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataDirectory() / "Directory4");

    Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const boost::filesystem::path& path)
        {
            files.emplace_back(path.generic_string());
        },
        true
        );
    std::sort(files.begin(), files.end());

    ISHIKO_TEST_ABORT_IF_NEQ(files.size(), 4);
    ISHIKO_TEST_FAIL_IF_NEQ(files[0], "../../data/Directory4/dir_1/file_1_1.txt");
    ISHIKO_TEST_FAIL_IF_NEQ(files[1], "../../data/Directory4/dir_2/file_2_1.txt");
    ISHIKO_TEST_FAIL_IF_NEQ(files[2], "../../data/Directory4/dir_2/file_2_2.txt");
    ISHIKO_TEST_FAIL_IF_NEQ(files[3], "../../data/Directory4/file_1.txt");
    ISHIKO_TEST_PASS();
}

void DirectoryTests::GetRegularFilesCountTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("Directory1");
    Directory directory(inputPath);

    size_t count = directory.getRegularFilesCount(false);

    ISHIKO_TEST_FAIL_IF_NEQ(count, 1);
    ISHIKO_TEST_PASS();
}

void DirectoryTests::GetRegularFilesCountTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("Directory2");
    Directory directory(inputPath);

    size_t count = directory.getRegularFilesCount(false);

    ISHIKO_TEST_FAIL_IF_NEQ(count, 2);
    ISHIKO_TEST_PASS();
}

void DirectoryTests::GetRegularFilesCountTest3(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("Directory4");
    Directory directory(inputPath);

    size_t nonRecursiveCount = directory.getRegularFilesCount(false);
    size_t recursiveCount = directory.getRegularFilesCount(true);

    ISHIKO_TEST_FAIL_IF_NEQ(nonRecursiveCount, 1);
    ISHIKO_TEST_FAIL_IF_NEQ(recursiveCount, 4);
    ISHIKO_TEST_PASS();
}
