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


#include <memory>
#include <string>

#include "mercury/_http/http_client.h"
#include "mercury/_http/http_client_interface.h"

using std::string;


/**
 * \class KanoWorld
 * \brief Provides access to Kano World Services Network API
 */
class KanoWorld
{
 public:
    /**
     * \brief Constructor
     *
     * \param client    (Optional) The HTTP client to use for requests
     */
    explicit KanoWorld(std::shared_ptr<IHTTPClient> client =
        std::make_shared<HTTPClient>());

    bool login(const string& username, const string& password,
               const bool verbose = false);
    bool logout(const bool verbose = false);
    bool refresh_token(string token, const bool verbose = false);

    string get_hostname(string config_filename);
    string get_refresh_header(string token);

    bool is_logged_in(const bool verbose = false);
    string whoami();


    /**
     * \brief Determine if the user's account has been verified with parental
     *        permission.
     */
    bool is_account_verified();

    const string data_filename;
    string get_token() const;
    string get_expiration_date() const;
    bool load_data();

 private:
    std::shared_ptr<IHTTPClient> http_client;
    std::string parse_token(const std::shared_ptr<JSON_Value> res) const;
    std::string parse_expiration_date(
        const std::shared_ptr<JSON_Value> res) const;
    string token;
    string expiration_date;
    bool save_data();
};


#endif  // MERCURY_KW_KW_H_
