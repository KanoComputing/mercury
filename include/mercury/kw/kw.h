/**
 * \file kw.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     Provides common functions to interact with Kano World Services
 *            network APIs
 *
 */


#ifndef INCLUDE_MERCURY_KW_KW_H_
#define INCLUDE_MERCURY_KW_KW_H_


#include <parson.h>

#include <atomic>
#include <chrono>  // NOLINT
#include <memory>
#include <mutex>  // NOLINT
#include <string>

#include "mercury/http/http_client_interface.h"
#include "mercury/utils/IEnvironment.h"


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
    explicit KanoWorld(
        const std::string& url = "",
        const std::shared_ptr<Mercury::HTTP::IHTTPClient>& client = nullptr,
        const std::shared_ptr<Mercury::Utils::IEnvironment>& env = nullptr);

    /**
     * \brief Logs out the current user
     *
     * The cache file is removed so that the login details are discarded.
     *
     * \param verbose Be more descriptive on the transaction details.
     *
     * \returns True if logout was successful
     */
    bool logout(const bool verbose = false);

    /**
     * \brief Returns whether the user is currently logged in
     *
     * A local token timestamp comparison is performed, to decide whether
     * it has expired.
     *
     * \param verbose Be more descriptive on the actions performed.
     *
     * \returns True if the current user is logged in.
     */
    bool is_logged_in(const bool verbose = false);

    /**
     * \brief Extract the Kano World username
     */
    std::string get_username() const;

    /**
     * \brief Set the Kano World username
     *
     * \param user        Value to set the token to.
     * \param save        Whether to save changes to disk
     */
    void set_username(const std::string& user, const bool save = true);

    /**
     * \brief Extract the authentication token
     */
    std::string get_token() const;

    /**
     * \brief Set the authentication token
     *
     * \param token_val   Value to set the token to.
     * \param save        Whether to save changes to disk
     */
    void set_token(const std::string& token_val, const bool save = true);

    /**
     * \brief Calls the refresh_token endpoint to request a new token
     *
     * On success, the token is saved locally for future reference
     *
     * \param token       The previously stored token
     * \param verbose     Be more descriptive on the transaction details
     *
     * \returns True if a new token was returned from the server.
     */
    bool refresh_token(const std::string& token, const bool verbose = false);

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
    std::chrono::milliseconds get_expiration_date() const;

    /**
     * \brief Set the authentication token
     *
     * \param expiration   Value to set the expiration to.
     * \param save         Whether to save changes to disk
     */
    void set_expiration_duration(
        const std::chrono::seconds& duration, const bool save = true);

    /**
     * \brief Set the authentication token
     *
     * \param expiration   Value to set the expiration to.
     * \param save         Whether to save changes to disk
     */
    void set_expiration_date(
        const std::chrono::milliseconds& timestamp, const bool save = true);

    // TODO: private
    bool load_data();

    /**
     * \brief Calls the login endpoint the username and password credentials.
     *
     * TODO: remove; this happens through webpages we can update live
     * \warning This will be removed in the future
     *
     * This is a login to the Kano World Services API
     *
     * \param user        The username to log in as
     * \param password    The password to the user account
     * \param verbose     Be more descriptive on the transaction details
     *
     * \returns True if login was successful, false otherwise
     */
    bool login(
        const std::string& username, const std::string& password,
        const bool verbose = false);

    // TODO: remove
    std::string whoami() const;
    std::string get_hostname(const std::string& config_filename);
    std::string get_refresh_header(const std::string& token);

 public:
    std::string data_filename;
    const std::string api_url;

 protected:
    /**
     * \brief
     */
    bool save_data();

 private:
    /**
     * \brief Perform the API call to determine if the account is verified.
     */
    bool is_account_verified_api() const;

    /**
     * \brief Check if the cached login token has expired.
     */
    bool is_token_expired() const;

    /**
     * \brief Extracts the token from an API response.
     */
    std::string parse_token(const std::shared_ptr<JSON_Value>& res) const;

    /**
     * \brief Extracts the expiration duration from an API response.
     */
    std::chrono::seconds parse_expiration_duration(
        const std::shared_ptr<JSON_Value>& res) const;

    /**
     * \brief Helper for initialising the api_url member variable
     */
    std::string init_api_url(const std::string& url) const;

 private:
    std::shared_ptr<Mercury::HTTP::IHTTPClient> http_client;
    std::string username;
    std::string token;
    std::chrono::milliseconds expiration_date;
    std::atomic<bool> is_verified_cache;
    std::mutex save_mutex;
};


};  // namespace KanoWorld
};  // namespace Mercury


#endif  // INCLUDE_MERCURY_KW_KW_H_
