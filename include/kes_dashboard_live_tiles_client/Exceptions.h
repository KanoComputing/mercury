/**
 * \file Exceptions.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_EXCEPTIONS_H_
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_EXCEPTIONS_H_


#include <parson.h>

#include <exception>
#include <memory>
#include <string>


namespace KESDLTC {
namespace internal {

/**
 * \class KESDLTClientException
 * \brief Base exception to throw when there is an error with this client
 */
class KESDLTClientException : public std::exception {
 public:
    explicit KESDLTClientException(
        const std::string& msg,
        const JSON_Value* data = nullptr):
        message(msg),
        data(data) {
        // NOLINT
        if (this->data != nullptr) {
            std::shared_ptr<char> dataStr(
                json_serialize_to_string_pretty(this->data),
                json_free_serialized_string);
            this->message = this->message + std::string(dataStr.get());
        }
    }

 public:
    const char *what() const noexcept(true) {
        return this->message.c_str();
    }

 private:
    std::string message;
    const JSON_Value* data;
};


/**
 * \class BrokenContractsException
 * \brief Exception thrown when the data the client expects doesn't match the
 *        data provided by the service.
 */
class BrokenContractsException : public KESDLTClientException {
 public:
    explicit BrokenContractsException(
        const std::string& msg,
        const JSON_Value* data = nullptr):
        // NOLINT
        KESDLTClientException(
            std::string("Broken KES API data contract: ") + msg,
            data) {}
};


/**
 * \class CorruptedCacheException
 * \brief Exception thrown when the data the client cached is malformed in
          any way when retrieving.
 */
class CorruptedCacheException : public KESDLTClientException {
 public:
    explicit CorruptedCacheException(
        const std::string& msg,
        const JSON_Value* data = nullptr):
        // NOLINT
        KESDLTClientException(
            std::string("Corrupted KES cache or malformed data: ") + msg,
            data) {}
};

}  // namespace internal
}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_EXCEPTIONS_H_
