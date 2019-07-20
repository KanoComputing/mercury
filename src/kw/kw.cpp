/**
 * \file kw.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 *  Kano World class methods implemntation
 */


#include "mercury/kw/kw.h"

#include <parson.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <ctime>
#include <iostream>
#include <memory>
#include <string>

#include "mercury/_http/http_client_interface.h"

using std::string;



KanoWorld::KanoWorld(std::shared_ptr<IHTTPClient> client) :
    http_client(client),
    data_filename(string(getenv("HOME")) + "/" + ".mercury_kw.json"),
    token(""),
    expiration_date("") {
}


/**
 * \brief Calls the login endpoint the username and password credentials.
 *
 * This is a login to the Kano World Services API
 *
 * \param username    The first parameter passed to the function
 * \param password    The second parameter passed to the function
 * \param verbose     Be more descriptive on the transaction details
 *
 * \returns True if login was successful, false otherwise.e
 */
bool KanoWorld::login(const string& username, const string& password,
                      bool verbose) {
    if (!username.length() || !password.length()) {
        return false;
    }

    const std::string body = "{\n\"username\": \"" + username +
        "\", \n\"password\": \"" + password + "\"\n}";

    std::shared_ptr<JSON_Value> res;

    try {
        res = this->http_client->POST(
            "https://worldapi-dev.kano.me/accounts/auth",
            body);
    } catch (const HTTPRequestFailedError& err) {
        if (verbose) {
            std::cout << err.what() << std::endl;
        }

        return false;
    } catch (const SessionInitError& err) {
        if (verbose) {
            std::cout << err.what() << std::endl;
        }

        return false;
    } catch (const std::exception& err) {
        if (verbose) {
            std::cout << "Unkown error: " << err.what() << std::endl;
        }

        return false;
    }

    this->token = this->parse_token(res);
    this->expiration_date = this->parse_expiration_date(res);
    save_data();

    if (verbose) {
        std::shared_ptr<char> resp_str(
            json_serialize_to_string(res.get()),
            json_free_serialized_string);
        std::cout << ">>> login SERVER RESPONSE: " << resp_str << std::endl;
        std::cout << ">>> Token: " << get_token() << std::endl;
        std::cout << ">>> Expiration date: " << get_expiration_date()
                  << std::endl;
    }

    return true;
}


/**
 * \brief Logs out the current user
 *
 * The cache file is removed so that the login details are discarded
 *
 * \param verbose     Be more descriptive on the transaction details
 *
 * \returns True if logout was successful
 */
bool KanoWorld::logout(bool verbose)
{
    struct stat cache;
    int rc = stat(data_filename.c_str(), &cache);

    if (rc != -1) {
        int rc = unlink(data_filename.c_str());
    }

    if (verbose) {
        std::cout << "logout - removing cache file success? "
                  << (rc == -1 ? "No" : "Yes") << std::endl;
    }
    return rc != -1;
}


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
bool KanoWorld::refresh_token(string token, bool verbose)
{
    if (!token.length()) {
        return false;
    }

    std::map<std::string, std::string> headers {
        std::make_pair("Authorization", "Bearer " + token)};

    std::shared_ptr<JSON_Value> res;

    try {
        res = this->http_client->GET(
            "https://worldapi-dev.kano.me/accounts/auth/refresh",
            headers);
    } catch (const HTTPRequestFailedError& err) {
        if (verbose) {
            std::cout << err.what() << std::endl;
        }

        return false;
    } catch (const SessionInitError& err) {
        if (verbose) {
            std::cout << err.what() << std::endl;
        }

        return false;
    } catch (const std::exception& err) {
        if (verbose) {
            std::cout << "Unkown error: " << err.what() << std::endl;
        }

        return false;
    }

    this->token = this->parse_token(res);
    this->expiration_date = this->parse_expiration_date(res);
    save_data();

    if (verbose) {
        std::shared_ptr<char> resp_str(
            json_serialize_to_string(res.get()),
            json_free_serialized_string);
        std::cout << ">>> refresh_token SERVER RESPONSE: " << resp_str
                  << std::endl;
        std::cout << ">>> Token: " << get_token() << std::endl;
        std::cout << ">>> Expiration date: " << get_expiration_date()
                  << std::endl;
    }

    return true;
}


/**
 * \brief Returns the hostname used to contact the Kano World API
 *
 * On success, the token is saved locally for future reference
 *
 * \param config_filename   Json filename that stores the API details
 *
 * \returns A string with the URL to the server
 */
string KanoWorld::get_hostname(string config_filename)
{
    // TODO: read from json configuration file
    return (string(""));
}


/**
 * \brief Returns the HTTP header needed to call the token "refresh" endpoint
 *
 * \param token    The token needed to submit the request
 *
 * \returns A string with the HTTP header
 */
string KanoWorld::get_refresh_header(string token)
{
    return (string("Authorization: Bearer " + token));
}


/**
 * \brief Returns wether the user is currently logged in
 *
 * A local token timestamp comparison is performed, to decide wether it has
 * expired
 *
 * \param verbose    Be more descriptive on the actions performed
 *
 * \returns True if the current user is logged in.
 */
bool KanoWorld::is_logged_in(bool verbose)
{
    std::time_t now = std::time(nullptr);

    if (!load_data()) {
        return false;
    }

    std::time_t duration = atol(expiration_date.c_str());

    if (!duration) {
        return false;
    }

    double seconds = difftime(now, duration);

    if (verbose) {
        char now_str[26];
        ctime_r(static_cast<const time_t*>(&now), now_str);

        char duration_str[26];
        ctime_r(static_cast<const time_t*>(&duration), duration_str);

        std::cout << ">>> Am_I_Logged_In() requested - Time: " << now << " - "
                  << now_str << std::endl;

        std::cout << ">>> Token expires: " << duration << " - "
                  << duration_str << std::endl;
        std::cout << ">>> Difference in seconds: " << seconds << std::endl;
        std::cout << ">>> Token valid? " << (seconds < 0 ? "Yes" : "No")
                  << std::endl;
    }

    return seconds < 0;
}


/**
 *   Not implemented yet
 */
std::string KanoWorld::whoami()
{
    return "";
}


/**
 * \brief Returns the token from the server response
 *
 * \returns A string with the complete JWT token
 */
std::string KanoWorld::parse_token(
        const std::shared_ptr<JSON_Value> res) const {
    if (res) {
        return json_object_dotget_string(json_object(res.get()), "data.token");
    }

    return "";
}


/**
 * \brief Returns the token expiration date from the server response
 *
 * \returns A string with the Unix timestamp representing the token expiration
 *          date
 */
std::string KanoWorld::parse_expiration_date(
        const std::shared_ptr<JSON_Value> res) const {
    if (res) {
        // For some reason, the Unix time returned by the server is divide by
        // 1000 so we convert it back into a Unix time here. See:
        // https://github.com/KanoComputing/kes-world-api/blob/develop/src/controllers/accounts.js#L35
        int conversion = 1000;
        string translate = json_object_dotget_string(
            json_object(res.get()), "data.duration");
        return std::to_string(std::stol(translate) * conversion);
    }

    return "";
}


std::string KanoWorld::get_token() const {
    return this->token;
}


std::string KanoWorld::get_expiration_date() const {
    return this->expiration_date;
}


/**
 * \brief Loads the cache data for the latest Kano World transaction
 *
 * The cache data contains the token and expiration timestamp
 *
 * \returns true if the data was successfully loaded.
 */
bool KanoWorld::load_data()
{
    std::shared_ptr<JSON_Value> user_data(
        json_parse_file(data_filename.c_str()),
        json_value_free);

    if (!user_data) {
        return false;
    }

    token = json_object_get_string(json_object(user_data.get()), "token");
    expiration_date = json_object_get_string(
        json_object(user_data.get()), "duration");

    return true;
}


/**
 * \brief Saves the data returned from the server on a local cache file.
 *
 * The cache data file is then used to peek at the login token and expiration
 * timestamp
 *
 * \returns true if the data was successfully saved.
 */
bool KanoWorld::save_data()
{
    std::shared_ptr<JSON_Value> user_data(
        json_value_init_object(),
        json_value_free);

    if (!user_data) {
        return false;
    }

    json_object_set_string(
        json_object(user_data.get()), "token", get_token().c_str());
    json_object_set_string(
        json_object(user_data.get()), "duration", get_expiration_date().c_str());

    JSON_Status rc = json_serialize_to_file(user_data.get(), data_filename.c_str());

    return rc == JSONSuccess;
}

/**
 * \warning Not implemented
 */
bool KanoWorld::is_account_verified() {
    return true;
}
