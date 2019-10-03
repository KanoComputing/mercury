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

#include "mercury/utils/Environment.h"

using std::string;

using Mercury::Utils::Environment;


Environment::Environment() {
    // Empty constructor.
}


Environment::~Environment() {
    // Empty destructor.
}


std::string Environment::get(const std::string& variable) const {
    const char* value = std::getenv(variable.c_str());
    if (value == nullptr) {
        return string("");
    } else {
        return string(value);
    }
}
