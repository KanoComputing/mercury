/**
 * \file TestFilesystem.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_UNIT_UTILS_TESTFILESYSTEM_H_
#define TEST_UNIT_UTILS_TESTFILESYSTEM_H_


#include <gtest/gtest.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <cstdlib>
#ifdef __cpp_lib_filesystem
#include <filesystem>
#else  // __cpp_lib_filesystem
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
namespace std {
    namespace filesystem = std::experimental::filesystem;
}
#endif  // __cpp_lib_filesystem
#include <memory>
#include <string>

#include "mercury/utils/Filesystem.h"
#include "mercury/utils/IFilesystem.h"


namespace Mercury {
namespace Utils {
namespace test {


/**
 * Check that users of the class can use it through a pointer of its interface.
 */
TEST(TestFilesystem, CanUseClassThroughInterfacePointer) {
    std::shared_ptr<Mercury::Utils::IFilesystem> sharedFilesystem =
        std::make_shared<Mercury::Utils::Filesystem>();

    std::unique_ptr<Mercury::Utils::IFilesystem> uniqueFilesystem =
        std::make_unique<Mercury::Utils::Filesystem>();

    EXPECT_TRUE(sharedFilesystem != nullptr);
    EXPECT_TRUE(uniqueFilesystem != nullptr);
}

/**
 * Check that creation of a directory with no name fails
 */
TEST(TestFilesystem, UntitledDirectoryCreationFails) {
    Mercury::Utils::Filesystem fs;
    EXPECT_FALSE(fs.create_directory(""));
}

/**
 * Check that a single directory can be created
 */
TEST(TestFilesystem, DirectoryCanBeCreated) {
    bool dir_exists;
    struct stat st;
    std::string path = "temptestdir";

    dir_exists = stat(path.c_str(), &st) == 0;
    EXPECT_FALSE(dir_exists);

    Mercury::Utils::Filesystem fs;
    EXPECT_TRUE(fs.create_directory(path));

    dir_exists = stat(path.c_str(), &st) == 0;
    EXPECT_TRUE(dir_exists);

    // Clean up
    std::filesystem::remove(path);
}


/**
 * Check that nested directories can be created
 */
TEST(TestFilesystem, DirectoriesCanBeCreated) {
    bool dir_exists;
    struct stat st;
    std::filesystem::path path("temp/test/dir");

    dir_exists = stat(path.string().c_str(), &st) == 0;
    EXPECT_FALSE(dir_exists);

    Mercury::Utils::Filesystem fs;
    EXPECT_TRUE(fs.create_directories(path.string()));

    dir_exists = stat(path.string().c_str(), &st) == 0;
    EXPECT_TRUE(dir_exists);

    // Clean up
    std::filesystem::remove_all(path.parent_path().parent_path().string());
}



}  // namespace test
}  // namespace Utils
}  // namespace Mercury


#endif  // TEST_UNIT_UTILS_TESTFILESYSTEM_H_
