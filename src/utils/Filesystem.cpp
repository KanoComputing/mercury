/**
 * \file Filesystem.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <string>
#include <vector>

#include "mercury/utils/Filesystem.h"
#include "mercury/utils/String.h"

using std::string;
using std::vector;


bool create_directory(const string& path, mode_t mode) {
// This function needs a reimplementation on Windows - sys/stat.h
#ifdef WIN32
    return true;
#else
    bool successful = true;
    struct stat st;

    // Check if the path already exists.
    if (stat(path.c_str(), &st) != 0) {
        // Directory does not exist, attempt to create.
        // EEXIST for race condition.
        if (mkdir(path.c_str(), mode) != 0 && errno != EEXIST) {
            successful = false;
        }

    // If path does exist, check if it is a valid directory.
    } else if (!S_ISDIR(st.st_mode)) {
        errno = ENOTDIR;
        successful = false;
    }
    return successful;
#endif
}


bool create_directories(const string& path, mode_t mode) {
    vector<string> directories = split(path, '/');

    for (int i = 0; i < directories.size(); i++) {
        if (directories[i].empty()) {
            continue;
        }
        vector<string> pathParts(
            directories.begin(),
            directories.begin() + i + 1);

        if (!create_directory(join(pathParts, "/"))) {
            return false;
        }
    }
    return true;
}
