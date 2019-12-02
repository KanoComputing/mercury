/**
 * \file Environment.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <cstdlib>
#include <string>

#ifdef WIN32
#include <windows.h>
#endif  // WIN32

#include "mercury/utils/Environment.h"

using std::string;

using Mercury::Utils::Environment;


std::string Environment::get(const std::string& variable) const {
#ifdef WIN32
    constexpr int kBuffsize = 4096;
    char value[kBuffsize];
    GetEnvironmentVariable(variable.c_str(), value, kBuffsize);
#else  // WIN32
    const char* value = std::getenv(variable.c_str());
#endif  // WIN32

    if (value == nullptr) {
        return string("");
    } else {
        return string(value);
    }
}
