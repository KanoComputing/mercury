/**
 * \file kw.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     Provides common functions to interact with Kano World Services network APIs
 *
 */

#ifndef INCLUDE_MERCURY_KW_KW_H_
#define INCLUDE_MERCURY_KW_KW_H_


#include <atomic>
#include <memory>
#include <string>

#include "mercury/http/http_client.h"
#include "mercury/http/http_client_interface.h"
#include "mercury/kw/APIConfig.h"

using Mercury::KanoWorld::APIConfig;
using std::make_shared;
using std::shared_ptr;
using std::string;


namespace Mercury {
namespace KanoWorld {


/**
 * \class KanoWorld
 * \brief Provides access to Kano World Services Network API
 */
class KanoWorld {
 public:
    /**
     * \brief Constructor
     *
     * \param client    (Optional) The HTTP client to use for requests
     */
    KanoWorld(
        const string& url = "",
        shared_ptr<Mercury::HTTP::IHTTPClient> client =
            make_shared<Mercury::HTTP::HTTPClient>());

    bool login(const string& username, const string& password,
               const bool verbose = false);
    bool logout(const bool verbose = false);
    bool refresh_token(const string& token, const bool verbose = false);

    string get_hostname(string config_filename);
    string get_refresh_header(const string& token);

    bool is_logged_in(const bool verbose = false);
    string whoami() const;

    /**
     * \brief Read from the cache if the account has been verified with
     *        parental permission
     */
    bool get_account_verified() const;
    /**
     * \brief Set the the account verified status
     *
     * \param verified    The value to set it to
     * \param save        Whether to save changes to disk
     */
    void set_account_verified(const bool verified, const bool save = true);
    /**
     * \brief Refresh the cached value for whether the user's account has been
     *        verified with parental permission.
     *
     * \param sticky   (Optional) Whether to use the cached value in the case
     *                 where the account has been seen to be verified or query
     *                 directly from the API every time.
     */
    bool refresh_account_verified(const bool sticky = false);

    /**
     * \brief Extract the authentication token
     */
    string get_token() const;
    /**
     * \brief Set the authentication token
     *
     * \param token_val   Value to set the token to.
     * \param save        Whether to save changes to disk
     */
    void set_token(const string& token_val, const bool save = true);

    /**
     * \brief Extract the authentication token
     */
    string get_expiration_date() const;
    /**
     * \brief Set the authentication token
     *
     * \param expiration   Value to set the expiration to.
     * \param save         Whether to save changes to disk
     */
    void set_expiration_date(const string& expiration,
                             const bool save = true);

    bool load_data();

 public:
    const string data_filename;
    const string api_url;

 private:
    /**
     * \brief Perform the API call to determine if the account is verified
     */
    bool is_account_verified_api() const;
    string parse_token(const shared_ptr<JSON_Value> res) const;
    string parse_expiration_date(const shared_ptr<JSON_Value> res) const;
    bool save_data();
    /**
     * \brief Helper for initialising the api_url member variable
     */
    std::string init_api_url(const std::string& url) const;

 private:
    shared_ptr<Mercury::HTTP::IHTTPClient> http_client;
    string token;
    string expiration_date;
    std::atomic<bool> is_verified_cache;
};


};  // namespace KanoWorld
};  // namespace Mercury


#endif  // INCLUDE_MERCURY_KW_KW_H_
