/**
 * \file IEnvironment.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_UTILS_IENVIRONMENT_H_
#define INCLUDE_MERCURY_UTILS_IENVIRONMENT_H_


#include <string>


namespace Mercury {
namespace Utils {

/**
 * \class IEnvironment
 * \brief Interface for an Environment utility class.
 */
class IEnvironment {
 public:  // Constructors & destructors.
    virtual ~IEnvironment() {}

 public:  // Methods.
    virtual std::string getenv(const std::string& variable) const = 0;
};

}  // namespace Utils
}  // namespace Mercury


#endif  // INCLUDE_MERCURY_UTILS_IENVIRONMENT_H_
