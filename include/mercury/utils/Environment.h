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
 * \brief Utility class which wraps standard C functions for environment
          manipulation.
 */
class Environment : public IEnvironment {
 public:  // Methods.
    std::string get(const std::string& variable) const override;
};

}  // namespace Utils
}  // namespace Mercury


#endif  // INCLUDE_MERCURY_UTILS_ENVIRONMENT_H_
