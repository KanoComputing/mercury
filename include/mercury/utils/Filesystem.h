/**
 * \file Filesystem.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_UTILS_FILESYSTEM_H_
#define INCLUDE_MERCURY_UTILS_FILESYSTEM_H_


#include <sys/stat.h>
#include <string>

// Windows does not understand mode_t as it is on Unix - sys/stat.h
#ifdef WIN32
    typedef int mode_t;
    using namespace std;
#else
    using std::string;
#endif


/**
 * \brief Essentially mkdir on Linux without -p.
 *        Replaceable by create_directory in C++17.
 *
 * param path  The path to the directory to create.
 * param mode  (Optional) as passed to mkdir(3).
 *
 * returns     Whether the operation was successful or not.
 */

// Workaround to using mode_t without preset S_* access mode flags
#ifdef WIN32
bool create_directory(
    const string& path,
    mode_t mode = 0);
#else
bool create_directory(
    const string& path,
    mode_t mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif


/**
 * \brief Essentially mkdir -p on Linux.
 *        Replaceable by create_directories in C++17.
 *
 * param path  The path to the directory to create.
 * param mode  (Optional) as passed to mkdir(3).
 *
 * returns     Whether the operation was successful or not.
 */
bool create_directories(
    const string& path,

// Avoid using unknown access flags on Windows
#ifdef WIN32
    mode_t mode = 0
#else
    mode_t mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH
#endif
);


#endif  // INCLUDE_MERCURY_UTILS_FILESYSTEM_H_
