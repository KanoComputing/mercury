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

// Windows does not understand about file ownership, etc - sys/stat.h
// Redefine mode_t to int as we are not going to use it
// And define enum types for compiler to digest correctly, not used anyways
#ifdef WIN32
    typedef int mode_t;
    using namespace std;

    enum modes {
        S_IRWXU, S_IRWXG, S_IROTH, S_IXOTH, S_ISDIR
    };

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
bool create_directory(
    const string& path,
    mode_t mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

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
    mode_t mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

#endif  // INCLUDE_MERCURY_UTILS_FILESYSTEM_H_
