/**
 * \file IFilesystem.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_UTILS_IFILESYSTEM_H_
#define INCLUDE_MERCURY_UTILS_IFILESYSTEM_H_


#include <sys/stat.h>
#include <string>


// Windows does not understand about file ownership, etc - sys/stat.h
// Redefine mode_t to int as we are not going to use it
// And define enum types for compiler to digest correctly, not used anyways
#ifdef WIN32
    typedef int mode_t;

    enum modes {
        S_IRWXU, S_IRWXG, S_IROTH, S_IXOTH, S_ISDIR
    };
#endif


namespace Mercury {
namespace Utils {

/**
 * \class IFilesystem
 * \brief Interface for an Filesystem utility class.
 */
class IFilesystem {
 public:  // Constructors & destructors.
    virtual ~IFilesystem() {}

 public:  // Methods.
    /**
     * \brief Essentially mkdir on Linux without -p.
     *        Replaceable by create_directory in C++17.
     *
     * param path  The path to the directory to create.
     * param mode  (Optional) as passed to mkdir(3).
     *
     * returns     Whether the operation was successful or not.
     */
    virtual bool create_directory(
        const std::string& path,
        mode_t mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) const = 0;
    /**
     * \brief Essentially mkdir -p on Linux.
     *        Replaceable by create_directories in C++17.
     *
     * param path  The path to the directory to create.
     * param mode  (Optional) as passed to mkdir(3).
     *
     * returns     Whether the operation was successful or not.
     */
    virtual bool create_directories(
        const std::string& path,
        mode_t mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) const = 0;
};

}  // namespace Utils
}  // namespace Mercury


#endif  // INCLUDE_MERCURY_UTILS_IFILESYSTEM_H_
