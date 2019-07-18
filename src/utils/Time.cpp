/**
 * \file Time.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <chrono>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;


double getTimestamp() {
    return duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    ).count();
}
