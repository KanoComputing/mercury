/**
 * \file kw.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 *  Kano World class methods implemntation
 */

#include <string>
#include <ctime>

using std::string;

#include "mercury/kw/kw.h"

#include <stdlib.h>
#include <parson.h>
#include <curl/curl.h>


KanoWorld::KanoWorld() :
    data_filename (string(getenv("HOME")) + "/" + ".mercury_kw.json"),
    token(""),
    expiration_date("")
{
}


/**
 *  Calls the "login" endpoint using the username and password credentials.
 *  On success, the new token and duration time are stored in the cache data file.
 */
bool KanoWorld::login(const string& username, const string& password, bool verbose)
{
    CURL *curl;
    CURLcode res;
    struct curl_slist *chunk = NULL;
    long code=0L;

    if (!username.length() || !password.length()) {
        return false;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {

        // TODO: use json library
        string payload = "{\n\"username\": \"" + username + "\", \n\"password\": \"" + password + "\"\n}";

        // Apply API expected headers
        chunk = curl_slist_append(chunk, "Accept: application/json");
        chunk = curl_slist_append(chunk, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        curl_easy_setopt(curl, CURLOPT_URL, "https://worldapi-dev.kano.me/accounts/auth");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, verbose ? 1L : 0L);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, payload.length());
        curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, payload.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_server_response);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    curl_slist_free_all(chunk);
    save_data();

    // True if server responds with HTTP OK
    if (code == HTTP_OKAY) {
        if (verbose) {
            printf (">>> login SERVER RESPONSE: %s\n", server_response.c_str());
            printf (">>> Token: %s\n", get_token().c_str());
            printf (">>> Expiration date: %s\n", get_expiration_date().c_str());
        }
        return true;
    }

    return false;

} // login


/**
 *  Calls the @refresh_token" endpoint to request a new token
 *  On success, the new token and duration time are stored in the cache data file.
 */
bool KanoWorld::refresh_token(string token, bool verbose)
{
    CURL *curl;
    CURLcode res;
    struct curl_slist *chunk = NULL;
    long code=0L;

    if (!token.length()) {
        return false;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {

        // Apply API expected headers
        chunk = curl_slist_append(chunk, "Accept: application/json");
        chunk = curl_slist_append(chunk, get_refresh_header(token).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        curl_easy_setopt(curl, CURLOPT_URL, "https://worldapi-dev.kano.me/accounts/auth/refresh");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, verbose ? 1L : 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_server_response);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    curl_slist_free_all(chunk);
    save_data();

    if (code == HTTP_OKAY) {
        if (verbose) {
            printf (">>> refresh_token SERVER RESPONSE: %s\n", server_response.c_str());
            printf (">>> Token: %s\n", get_token().c_str());
            printf (">>> Expiration date: %s\n", get_expiration_date().c_str());
        }
        save_data();
        return true;
    }

    return false;

} // refresh_token()



/**
 *   Returns the host name from the configuration file
 */
string KanoWorld::get_hostname(string config_filename)
{
    // TODO: read from json configuration file
    return (string(""));
}


/**
 *   Returns the HTTP header needed to call the token "refresh" endpoint
 */
string KanoWorld::get_refresh_header(string token)
{
    return (string("Authorization: Bearer " + token));
}


/**
 *   libcurl callback function, allows to collect the data response from the server,
 *   which in this case is a json object.
 *
 *   See libCurl CURLOPT_WRITEFUNCTION and CURLOPT_WRITEDATA options.
 *   The WRITEDATA option is used to pass the class instance to safe the data for later processing.
 */
size_t KanoWorld::callback_server_response(void *ptr, size_t size, size_t nmemb, void *user_data)
{
    // Save the server's response in a class string
    KanoWorld *pkw = (KanoWorld *) user_data;
    pkw->server_response = string((char *) ptr);

    return size * nmemb;
}


/**
 *   Returns true when the cached token duration time has not expired yet,
 *   false otherwise. Call the refresh_token API in such case.
 */
bool KanoWorld::am_i_logged_in(bool verbose)
{
    std::time_t now = std::time(nullptr);

    if (!load_data()) {
        return false;
    }

    std::time_t duration = atol(expiration_date.c_str());
    double seconds;

    if (!duration) {
        return false;
    }

    seconds = difftime(now, duration);

    if (verbose) {
        printf (">>> Am_I_Logged_In() requested - Time: %ld - %s", now, ctime((const time_t *) &now));
        printf (">>> Token expires: %ld - %s", duration, ctime((const time_t *) &duration));
        printf (">>> Difference in seconds: %f.3\n", seconds);
        printf (">>> Token valid? %s\n", (seconds < 0 ? "Yes" : "No"));
    }

    return (seconds < 0);
}
    

/**
 *   Not implemented yet
 */
string KanoWorld::whoami()
{
    return string("");
}


/**
 *   Collects and returns the token from the Server Response data
 */
string KanoWorld::get_token()
{
    JSON_Value *schema = json_parse_string(server_response.c_str());
    if (schema) {
        token = string(json_object_dotget_string(json_object(schema), "data.token"));
    }

    return token;
}


/**
 *   Collects and returns the token expiration date, "duration" field,
 *   from the Server Response data.
 */
string KanoWorld::get_expiration_date()
{
    JSON_Value *schema = json_parse_string(server_response.c_str());
    if (schema) {

        // For some reason, the Unix time returned by the server is divide by 1000
        // So we convert it back into a Unix time here. See:
        // https://github.com/KanoComputing/kes-world-api/blob/develop/src/controllers/accounts.js#L35
        long conversion = 1000;
        string translate = string(json_object_dotget_string(json_object(schema), "data.duration"));
        expiration_date = string( std::to_string (std::stol(translate.c_str()) * conversion) );
    }

    return expiration_date;
}


/**
 *   Loads the data from the cached file.
 */
bool KanoWorld::load_data()
{
    JSON_Value *user_data = json_parse_file(data_filename.c_str());
    if (!user_data) {
        return false;
    }

    token = json_object_get_string(json_object(user_data), "token");
    expiration_date = json_object_get_string(json_object(user_data), "duration");

    return true;
}


/**
 *   Saves the server response data fields into the cache local file.
 */
bool KanoWorld::save_data()
{
    JSON_Status rc;
    JSON_Value *user_data = json_value_init_object();

    if (!user_data) {
        return false;
    }

    json_object_set_string(json_object(user_data), "token", get_token().c_str());
    json_object_set_string(json_object(user_data), "duration", get_expiration_date().c_str());

    rc = json_serialize_to_file(user_data, data_filename.c_str());
    json_value_free(user_data);

    return (rc == JSONSuccess);
}
