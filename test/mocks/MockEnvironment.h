/**
 * \file MockEnvironment.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_MOCKS_MOCKENVIRONMENT_H_
#define TEST_MOCKS_MOCKENVIRONMENT_H_


#include <gmock/gmock.h>

#include <string>

#include "mercury/utils/IEnvironment.h"


namespace Mercury {
namespace Utils {
namespace test {

/**
 * \class MockEnvironment
 * \brief Interface for an MockEnvironment utility class.
 */
class MockEnvironment : public Mercury::Utils::IEnvironment {
 public:  // IEnvironment Methods.
    MOCK_CONST_METHOD1(
        get,
        std::string(const std::string& variable));
};

}  // namespace test
}  // namespace Utils
}  // namespace Mercury


#endif  // TEST_MOCKS_MOCKENVIRONMENT_H_
