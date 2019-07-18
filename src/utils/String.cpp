/**
 * \file String.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <sstream>
#include <string>
#include <vector>

using std::getline;
using std::string;
using std::stringstream;
using std::vector;


vector<string> split(const string& str, char delimiter) {
    vector<string> parts;
    stringstream stringStream(str);
    string chunk;

    while (getline(stringStream, chunk, delimiter)) {
        parts.push_back(chunk);
    }
    return parts;
}


string join(const vector<string>& parts, const string& delimiter) {
    bool initialised = false;
    string result = "";

    for (auto &part : parts) {
        if (!initialised) {
            initialised = true;
            result += part;
        } else {
            result += delimiter + part;
        }
    }
    return result;
}
