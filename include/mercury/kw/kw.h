/**
 * \file kw.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     Provides common functions to interact with Kano World Services network APIs
 *
 */

#ifndef MERCURY_KW_H
#define MERCURY_KW_H

#define HTTP_OKAY 200

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
    KanoWorld();
    ~KanoWorld();

    bool login(string username, string password, bool verbose);
    bool refresh_token(string token, bool verbose);

    string get_hostname(string config_filename);
    string get_refresh_header(string token);

    static size_t callback_server_response(void *ptr, size_t size, size_t nmemb, void *user_data);

    bool am_i_logged_in(bool verbose);
    string get_token(void);
    string get_expiration_date(void);
    bool save_data(void);
    bool load_data(void);
    string whoami(void);

    string server_response;
    string data_filename;
    string token;
    string expiration_date;
};

#endif  // MERCURY_KW_H
