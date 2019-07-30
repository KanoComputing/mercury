/**
 * \file kw_utils_mixin.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Fixtures mixin for interacting with Kano World to set up the
 *        KanoWorld() instance
 *
 */


#ifndef TEST_FIXTURES_KW_UTILS_MIXIN_H_
#define TEST_FIXTURES_KW_UTILS_MIXIN_H_


#include <gmock/gmock.h>

#include <test/fixtures/kw_api.h>
#include <test/mocks/mock_http_client.h>

#include <memory>
#include <string>

using Mercury::KanoWorld::KanoWorld;


class KWUtils {
 public:
     KWUtils() :
        username("testaccount"),
        password("testpassword"),
        auth_success(load_response("accounts/auth/login_success.json")),
        client(std::make_shared<MockHTTPClient>()),
        kw(KanoWorldAPI::URL, this->client) {}

 protected:
    void login() {
        const std::string login_body = "{\n\"username\": \"" + username +
            "\", \n\"password\": \"" + password + "\"\n}";
        ON_CALL(
            *this->client,
            POST_impl(
                KanoWorldAPI::AUTH_ENDPOINT,
                login_body,
                testing::_))
            .WillByDefault(testing::Return(this->auth_success));

        std::cout << "Logging in: "
                  << kw.login(this->username, this->password, true)
                  << std::endl;
    }

    const std::string username;
    const std::string password;
    const std::shared_ptr<JSON_Value> auth_success;
    std::shared_ptr<MockHTTPClient> client;
    KanoWorld kw;
};


#endif  // TEST_FIXTURES_KW_UTILS_MIXIN_H_
