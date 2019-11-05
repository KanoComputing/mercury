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

#ifdef WIN32
  #include <direct.h>
  #include <windows.h>
#endif

#include <string>
#include <vector>

#include "mercury/utils/Filesystem.h"
#include "mercury/utils/String.h"

using std::string;
using std::vector;


bool create_directory(const string& path, mode_t mode) {
    bool successful = true;
    struct stat st;

    // Check if the path already exists.
    if (stat(path.c_str(), &st) != 0) {
        // Directory does not exist, attempt to create.
        // EEXIST for race condition.

// mkdir is a different function call on Windows POSIX interface
#ifdef WIN32
        if (_mkdir(path.c_str()) != 0 && errno != EEXIST) {
            successful = false;
        }
#else
        if (mkdir(path.c_str(), mode) != 0 && errno != EEXIST) {
            successful = false;
        }
#endif

// If path does exist, check if it is a valid directory.
// On windows, S_ISDIR does not seem to exist, use a native Windows API
#ifdef WIN32
        else {
            DWORD file_type = GetFileAttributesA(path.c_str());
            if ((file_type != INVALID_FILE_ATTRIBUTES) || !(file_type & FILE_ATTRIBUTE_DIRECTORY)) {
                // Either the pathname is not found, or it is not a directory
                errno = ENOTDIR;
                successful = false;
            }
        }
#else
        else if (!S_ISDIR(st.st_mode)) {
            errno = ENOTDIR;
            successful = false;
        }
#endif
    }
    return successful;
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
