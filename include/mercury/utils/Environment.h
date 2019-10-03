/**
 * \file Environment.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_UTILS_ENVIRONMENT_H_
#define INCLUDE_MERCURY_UTILS_ENVIRONMENT_H_


#include <string>

#include "mercury/utils/IEnvironment.h"


namespace Mercury {
namespace Utils {

/**
 * \class Environment
 * \brief Interface for an Environment utility class.
 */
class Environment : public IEnvironment {
 public:  // Constructors & destructors.
    Environment();
    ~Environment();

 public:  // Methods.
    std::string getenv(const std::string& variable) const override;
};

}  // namespace Utils
}  // namespace Mercury


#endif  // INCLUDE_MERCURY_UTILS_ENVIRONMENT_H_
