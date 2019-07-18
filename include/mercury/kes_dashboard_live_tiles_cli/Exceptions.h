/**
 * \file Exceptions.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_EXCEPTIONS_H_
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_EXCEPTIONS_H_


#include <parson.h>

#include <exception>
#include <memory>
#include <string>

using std::string;
using std::shared_ptr;


/**
 * \class KESDLTClientException
 * \brief Base exception to throw when there is an error with this client
 */
class KESDLTClientException : public std::exception {
 public:
    explicit KESDLTClientException(const string& msg, const JSON_Value* data = nullptr) :
        message(msg), data(data) {

        if (this->data != nullptr) {
            shared_ptr<char> dataStr(
                json_serialize_to_string_pretty(this->data),
                json_free_serialized_string);

            this->message = this->message + string(dataStr.get());
        }
    }

 public:
    const char *what() const noexcept(true) {
        return this->message.c_str();
    }

 private:
    string message;
    const JSON_Value* data;
};


/**
 * \class BrokenContractsException
 * \brief Exception thrown when the data the client expects doesn't match the
 *        data provided by the service.
 */
class BrokenContractsException : public KESDLTClientException {
 public:
    BrokenContractsException(const string& msg, const JSON_Value* data = nullptr) :
        KESDLTClientException(
            string("Broken KES API data contract: ") + msg,
            data
        ) {}
};


/**
 * \class CorruptedCacheException
 * \brief Exception thrown when the data the client cached is malformed in
          any way when retrieving.
 */
class CorruptedCacheException : public KESDLTClientException {
 public:
    explicit CorruptedCacheException(const string& msg, const JSON_Value* data = nullptr) :
        KESDLTClientException(
            string("Corrupted KES cache or malformed data: ") + msg,
            data
        ) {}
};


#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_EXCEPTIONS_H_
