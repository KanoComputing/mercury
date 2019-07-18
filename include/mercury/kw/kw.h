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

    bool login(const string& username, const string& password, bool verbose);
    bool logout(bool verbose);
    bool refresh_token(string token, bool verbose);

    string get_hostname(string config_filename);
    string get_refresh_header(string token);

    static size_t callback_server_response(void *ptr, size_t size, size_t nmemb, void *user_data);

    bool is_logged_in(bool verbose);
    string whoami();

    string data_filename;
    string token;
    string expiration_date;
    string get_token();
    string get_expiration_date();
    bool load_data();

 private:
    bool save_data();
    string server_response;
};

#endif  // MERCURY_KW_H
