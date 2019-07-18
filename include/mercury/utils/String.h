/**
 * \file String.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_UTILS_STRING_H_
#define INCLUDE_MERCURY_UTILS_STRING_H_


#include <string>
#include <vector>

using std::string;
using std::vector;


/**
 * \brief TODO
 */
vector<string> split(const string& path, char delimiter);

/**
 * \brief TODO
 */
string join(const vector<string>& parts, const string& delimiter);


#endif  // INCLUDE_MERCURY_UTILS_STRING_H_
