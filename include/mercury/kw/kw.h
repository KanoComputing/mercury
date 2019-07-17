/**
 * \file kw.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     Provides common functions to interact with Kano World Services network APIs
 *
 */

#ifndef MERCURY_KW_KW_H_
#define MERCURY_KW_KW_H_

#include <string>
using std::string;

/**
 * \class KanoWorld
 * \brief Provides access to Kano World Services Network API
 */
class KanoWorld
{
 public:
    /**
     * \brief Sets the system wallpaper.
     */
    bool login(string username, string password, bool verbose);
    bool refresh_token(string token, bool verbose);

    string get_hostname(string config_filename);
    string get_refresh_header(string token);

    static size_t write_function(void *ptr, size_t size, size_t nmemb, void *stream);

    bool am_i_logged_in(void);
    string whoami(void);
};

#endif  // MERCURY_KW_KW_H_
