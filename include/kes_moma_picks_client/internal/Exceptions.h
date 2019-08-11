/**
 * \file Exceptions.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_EXCEPTIONS_H_
#define INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_EXCEPTIONS_H_


#include <parson.h>

#include <exception>
#include <memory>
#include <string>


namespace KESMPC {
namespace internal {

/**
 * \class KESMPClientException
 * \brief Base exception to throw when there is an error with this client
 */
class KESMPClientException : public std::exception {
 public:
    explicit KESMPClientException(
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
class BrokenContractsException : public KESMPClientException {
 public:
    explicit BrokenContractsException(
        const std::string& msg,
        const JSON_Value* data = nullptr):
        // NOLINT
        KESMPClientException(
            std::string("Broken KES API data contract: ") + msg,
            data) {}
};


/**
 * \class CorruptedCacheException
 * \brief Exception thrown when the data the client cached is malformed in
          any way when retrieving.
 */
class CorruptedCacheException : public KESMPClientException {
 public:
    explicit CorruptedCacheException(
        const std::string& msg,
        const JSON_Value* data = nullptr):
        // NOLINT
        KESMPClientException(
            std::string("Corrupted KES cache or malformed data: ") + msg,
            data) {}
};

}  // namespace internal
}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_EXCEPTIONS_H_
