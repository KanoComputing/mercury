/**
 * \file kw.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 *  Kano World class methods implemntation
 */


#include <parson.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <chrono>  // NOLINT
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include "mercury/http/http_client_interface.h"
#include "mercury/kw/APIConfig.h"
#include "mercury/kw/kw.h"

#include "mercury/utils/Time.h"

using Mercury::HTTP::IHTTPClient;
using Mercury::HTTP::HTTPRequestFailedError;
using Mercury::HTTP::SessionInitError;

using Mercury::KanoWorld::APIConfig;
using Mercury::KanoWorld::KanoWorld;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::cout;
using std::endl;
using std::exception;
using std::map;
using std::make_pair;
using std::shared_ptr;
using std::string;


KanoWorld::KanoWorld(const string& url, shared_ptr<IHTTPClient> client) :
        http_client(client),
        data_filename(string(getenv("HOME")) + "/.mercury_kw.json"),
        token(""),
        api_url(init_api_url(url)),
        expiration_date(0),
        is_verified_cache(false) {
    load_data();
}


bool KanoWorld::login(const string& user, const string& password,
                      const bool verbose) {
    if (!user.length() || !password.length()) {
        return false;
    }

    const string body = "{\n\"username\": \"" + user +
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

    this->set_token(this->parse_token(res), false);
    this->set_expiration_duration(this->parse_expiration_duration(res), false);
    this->save_data();

    if (verbose) {
        shared_ptr<char> resp_str(
            json_serialize_to_string(res.get()),
            json_free_serialized_string);
        cout << "login SERVER RESPONSE: " << resp_str << endl;
        cout << "Token: " << get_token() << endl;
        cout << "Expiration date: " << get_expiration_date().count() << endl;
    }

    return true;
}


bool KanoWorld::logout(const bool verbose) {
    struct stat cache;
    int rc = stat(this->data_filename.c_str(), &cache);

    if (rc != -1) {
        int rc = unlink(this->data_filename.c_str());
    }

    if (verbose) {
        cout << "logout - removing cache file success? "
             << (rc == -1 ? "No" : "Yes") << endl;
    }

    this->set_token("", false);
    this->set_expiration_date(milliseconds(0), false);
    this->set_account_verified(false, false);
    this->save_data();

    return rc != -1;
}


std::string KanoWorld::get_username() const {
    return this->username;
}


/**
 * \warning Currently does no validation on the username, just blindly sets it.
 */
void KanoWorld::set_username(const std::string& user, const bool save) {
    this->username = user;

    if (save) {
        this->save_data();
    }
}


bool KanoWorld::refresh_token(const string& token, const bool verbose) {
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

    this->set_token(this->parse_token(res), false);
    this->set_expiration_duration(this->parse_expiration_duration(res), false);
    this->save_data();

    if (verbose) {
        shared_ptr<char> resp_str(
            json_serialize_to_string(res.get()),
            json_free_serialized_string);
        cout << "refresh_token SERVER RESPONSE: " << resp_str << endl;
        cout << "Token: " << get_token() << endl;
        cout << "Expiration date: " << get_expiration_date().count() << endl;
    }

    return true;
}


/**
 * \brief Returns the hostname used to contact the Kano World API
 *
 * \param config_filename   Json filename that stores the API details
 *
 * \returns A string with the URL to the server
 */
string KanoWorld::get_hostname(const string& config_filename) {
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
string KanoWorld::get_refresh_header(const string& token) {
    return (string("Authorization: Bearer " + token));
}


bool KanoWorld::is_logged_in(const bool verbose) {
    return !this->is_token_expired();
}


bool KanoWorld::is_token_expired() const {
    return
        duration_cast<milliseconds>(system_clock::now().time_since_epoch()) >
        this->get_expiration_date();
}


/**
 * \warning Not implemented yet.
 */
string KanoWorld::whoami() const {
    return "";
}


/**
 * \brief Returns the token from the server response
 *
 * \returns A string with the complete JWT token
 */
string KanoWorld::parse_token(const shared_ptr<JSON_Value>& res) const {
    if (!res) {
        return "";
    }

    const JSON_Object* const data = json_value_get_object(res.get());

    if (!json_object_dothas_value_of_type(data, "data.token", JSONString)) {
        return "";
    }

    return json_object_dotget_string(data, "data.token");
}


/**
 * \brief Returns the token expiration date from the server response
 *
 * \returns A timestamp in milliseconds when the token will expire.
 */
seconds KanoWorld::parse_expiration_duration(
    const shared_ptr<JSON_Value>& res) const {

    if (!res) {
        return seconds(0);
    }

    const JSON_Object* const data = json_value_get_object(res.get());

    if (!json_object_dothas_value_of_type(data, "data.duration", JSONString)) {
        return seconds(0);
    }

    string duration_str = json_object_dotget_string(data, "data.duration");
    return seconds(std::stoll(duration_str));
}


string KanoWorld::get_token() const {
    return this->token;
}


void KanoWorld::set_token(const string& token_val, const bool save) {
    this->token = token_val;

    if (save) {
        this->save_data();
    }
}


milliseconds KanoWorld::get_expiration_date() const {
    return this->expiration_date;
}


/**
 * \warning Currently does no validation on the date, just blindly sets it.
 */
void KanoWorld::set_expiration_duration(
    const seconds& duration, const bool save) {

    milliseconds timestamp =
        duration_cast<milliseconds>(system_clock::now().time_since_epoch()) +
        duration_cast<milliseconds>(duration);

    this->set_expiration_date(timestamp, save);
}


/**
 * \warning Currently does no validation on the date, just blindly sets it.
 */
void KanoWorld::set_expiration_date(
    const milliseconds& timestamp, const bool save) {

    this->expiration_date = timestamp;

    if (save) {
        this->save_data();
    }
}


/**
 * \brief Loads the cache data for the latest Kano World transaction
 *
 * The cache data contains the token and expiration timestamp
 *
 * \returns true if the data was successfully loaded.
 */
bool KanoWorld::load_data() {
    shared_ptr<JSON_Value> user_data(
        json_parse_file(this->data_filename.c_str()),
        json_value_free);

    if (!user_data) {
        return false;
    }

    const JSON_Object* const data = json_value_get_object(user_data.get());

    if (json_object_has_value_of_type(data, "username", JSONString)) {
        this->set_username(json_object_get_string(data, "username"), false);
    }
    if (json_object_has_value_of_type(data, "token", JSONString)) {
        this->set_token(json_object_get_string(data, "token"), false);
    }
    if (json_object_has_value_of_type(data, "duration", JSONNumber)) {
        milliseconds timestamp(static_cast<int64_t>(
            json_object_get_number(data, "duration")));
        this->set_expiration_date(timestamp, false);
    }
    if (json_object_has_value_of_type(data, "is_verified", JSONBoolean)) {
        this->set_account_verified(
            json_object_get_boolean(data, "is_verified"), false);
    }

    this->save_data();
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
bool KanoWorld::save_data() {
    shared_ptr<JSON_Value> user_data(
        json_value_init_object(),
        json_value_free);

    if (!user_data) {
        return false;
    }

    JSON_Object* data = json_value_get_object(user_data.get());

    json_object_set_string(data, "username", this->get_username().c_str());
    json_object_set_string(data, "token", this->get_token().c_str());
    json_object_set_number(
        data, "duration", this->get_expiration_date().count());
    json_object_set_boolean(data, "is_verified", this->get_account_verified());

    JSON_Status rc = json_serialize_to_file_pretty(
        user_data.get(), this->data_filename.c_str());

    return rc == JSONSuccess;
}


bool KanoWorld::get_account_verified() const {
    return this->is_verified_cache;
}


void KanoWorld::set_account_verified(const bool verified, const bool save) {
    this->is_verified_cache = verified;

    if (save) {
        this->save_data();
    }
}


/**
 * \warning Implementation not finalised
 */
bool KanoWorld::refresh_account_verified(const bool sticky) {
    if (sticky && this->get_account_verified()) {
        return true;
    }

    this->set_account_verified(this->is_account_verified_api(), true);

    return this->get_account_verified();
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

    const JSON_Object* const data = json_value_get_object(response.get());

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


string KanoWorld::init_api_url(const std::string& url) const {
    if (!url.empty()) {
        return url;
    }

    return APIConfig().get_api_url();
}
