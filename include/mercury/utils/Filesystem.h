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

#include "mercury/utils/IFilesystem.h"



namespace Mercury {
namespace Utils {

/**
 * \class Filesystem
 * \brief Utility class which wraps standard C functions for filesystem
          manipulation.
 */
class Filesystem : public IFilesystem {
 public:  // Methods.
    bool create_directory(
        const std::string& path,
        mode_t mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) const override;
    bool create_directories(
        const std::string& path,
        mode_t mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) const override;
};

}  // namespace Utils
}  // namespace Mercury

#endif  // INCLUDE_MERCURY_UTILS_FILESYSTEM_H_
