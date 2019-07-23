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

using std::cout;
using std::endl;
using std::exception;
using std::map;
using std::make_pair;
using std::shared_ptr;
using std::string;


KanoWorld::KanoWorld(const string& url, shared_ptr<IHTTPClient> client) :
    http_client(client),
    data_filename(string(getenv("HOME")) + "/" + ".mercury_kw.json"),
    token(""),
    api_url(url),
    expiration_date(""),
    is_verified_cache(false) {
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
                      const bool verbose) {
    if (!username.length() || !password.length()) {
        return false;
    }

    const string body = "{\n\"username\": \"" + username +
        "\", \n\"password\": \"" + password + "\"\n}";

    shared_ptr<JSON_Value> res;

    try {
        res = this->http_client->POST(this->api_url + "/accounts/auth", body);
    } catch (const HTTPRequestFailedError& err) {
        if (verbose) {
            cout << err.what() << endl;
        }

        // TODO: Do we actually want to log out in this scenario?
        this->logout();
        return false;
    } catch (const SessionInitError& err) {
        if (verbose) {
            cout << err.what() << endl;
        }

        // TODO: Do we actually want to log out in this scenario?
        this->logout();
        return false;
    } catch (const exception& err) {
        if (verbose) {
            cout << "Unkown error: " << err.what() << endl;
        }

        // TODO: Do we actually want to log out in this scenario?
        this->logout();
        return false;
    }

    if (!res) {
        if (verbose) {
            cout << "Response was empty" << endl;
        }

        return false;
    }

    this->token = this->parse_token(res);
    this->expiration_date = this->parse_expiration_date(res);
    this->save_data();

    if (verbose) {
        shared_ptr<char> resp_str(
            json_serialize_to_string(res.get()),
            json_free_serialized_string);
        cout << ">>> login SERVER RESPONSE: " << resp_str << endl;
        cout << ">>> Token: " << get_token() << endl;
        cout << ">>> Expiration date: " << get_expiration_date() << endl;
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
bool KanoWorld::logout(const bool verbose)
{
    struct stat cache;
    int rc = stat(data_filename.c_str(), &cache);

    if (rc != -1) {
        int rc = unlink(data_filename.c_str());
    }

    if (verbose) {
        cout << "logout - removing cache file success? "
                  << (rc == -1 ? "No" : "Yes") << endl;
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
bool KanoWorld::refresh_token(string token, const bool verbose)
{
    if (!token.length()) {
        return false;
    }

    map<string, string> headers {
        make_pair("Authorization", "Bearer " + token)};

    shared_ptr<JSON_Value> res;

    try {
        res = this->http_client->GET(
            this->api_url + "/accounts/auth/refresh", headers);
    } catch (const HTTPRequestFailedError& err) {
        if (verbose) {
            cout << err.what() << endl;
        }

        return false;
    } catch (const SessionInitError& err) {
        if (verbose) {
            cout << err.what() << endl;
        }

        return false;
    } catch (const exception& err) {
        if (verbose) {
            cout << "Unkown error: " << err.what() << endl;
        }

        return false;
    }

    this->token = this->parse_token(res);
    this->expiration_date = this->parse_expiration_date(res);
    this->save_data();

    if (verbose) {
        shared_ptr<char> resp_str(
            json_serialize_to_string(res.get()),
            json_free_serialized_string);
        cout << ">>> refresh_token SERVER RESPONSE: " << resp_str << endl;
        cout << ">>> Token: " << get_token() << endl;
        cout << ">>> Expiration date: " << get_expiration_date() << endl;
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
bool KanoWorld::is_logged_in(const bool verbose)
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

        cout << ">>> Am_I_Logged_In() requested - Time: " << now << " - "
             << now_str << endl;

        cout << ">>> Token expires: " << duration << " - "
             << duration_str << endl;
        cout << ">>> Difference in seconds: " << seconds << endl;
        cout << ">>> Token valid? " << (seconds < 0 ? "Yes" : "No") << endl;
    }

    return seconds < 0;
}


/**
 *   Not implemented yet
 */
string KanoWorld::whoami()
{
    return "";
}


/**
 * \brief Returns the token from the server response
 *
 * \returns A string with the complete JWT token
 */
string KanoWorld::parse_token(
        const shared_ptr<JSON_Value> res) const {
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
 *
 */
string KanoWorld::parse_expiration_date(
        const shared_ptr<JSON_Value> res) const {
    if (res) {
        // For some reason, the Unix time returned by the server is divide by
        // 1000 so we convert it back into a Unix time here. See:
        // https://github.com/KanoComputing/kes-world-api/blob/develop/src/controllers/accounts.js#L35
        int conversion = 1000;
        string translate = json_object_dotget_string(
            json_object(res.get()), "data.duration");

        uint64_t converted_time = stol(translate);
        converted_time *= conversion;
        return std::to_string(converted_time);
    }

    return "";
}


string KanoWorld::get_token() const {
    return this->token;
}


string KanoWorld::get_expiration_date() const {
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
    shared_ptr<JSON_Value> user_data(
        json_parse_file(data_filename.c_str()),
        json_value_free);

    if (!user_data) {
        return false;
    }

    this->token = json_object_get_string(
        json_object(user_data.get()), "token");
    this->expiration_date = json_object_get_string(
        json_object(user_data.get()), "duration");
    this->is_verified_cache = json_object_get_boolean(
        json_object(user_data.get()), "is_verified");

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
    shared_ptr<JSON_Value> user_data(
        json_value_init_object(),
        json_value_free);

    if (!user_data) {
        return false;
    }

    json_object_set_string(
        json_object(user_data.get()), "token", get_token().c_str());
    json_object_set_string(
        json_object(user_data.get()), "duration",
                    get_expiration_date().c_str());
    json_object_set_boolean(
        json_object(user_data.get()), "is_verified",
                    this->is_verified_cache);

    JSON_Status rc = json_serialize_to_file(
        user_data.get(), data_filename.c_str());

    return rc == JSONSuccess;
}


/**
 * \warning Implementation not finalised
 */
bool KanoWorld::is_account_verified(const bool cache) {
    this->load_data();

    if (cache && this->is_verified_cache) {
        return true;
    }

    this->is_verified_cache = this->is_account_verified_api();
    this->save_data();

    return this->is_verified_cache;
}


void KanoWorld::clear_account_verified_cache() {
    this->load_data();
    this->is_verified_cache = false;
    this->save_data();
}


/**
 * \warning Implementation not finalised
 */
bool KanoWorld::is_account_verified_api() const {
    string auth_token = this->get_token();

    if (auth_token.empty()) {
        return false;
    }

    map<string, string> headers {
        { "Authorization", "Bearer " + auth_token }
    };

    shared_ptr<JSON_Value> response;

    try {
        response = this->http_client->GET(
            this->api_url + "/users/me", headers);
    } catch (const exception& e) {
        return false;
    }

    const JSON_Object *data = json_value_get_object(response.get());

    if (!json_object_dothas_value_of_type(
            data, "data.user.isVerified", JSONBoolean)) {
        return false;
    }

    int verified = json_object_dotget_boolean(data, "data.user.isVerified");

    if (verified == -1) {
        return false;
    }

    return static_cast<bool>(verified);
}
