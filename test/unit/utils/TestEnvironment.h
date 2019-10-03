/**
 * \file TestEnvironment.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_UNIT_UTILS_TESTENVIRONMENT_H_
#define TEST_UNIT_UTILS_TESTENVIRONMENT_H_


#include <gtest/gtest.h>
#include <stdlib.h>

#include <cstdlib>
#include <string>

#include "mercury/utils/Environment.h"
#include "test/fixtures/EnvironmentFixture.h"


namespace Mercury {
namespace Utils {
namespace test {


/**
 * Check that Environment.getenv() returns an empty string for an environment
 * variable that is not set.
 */
TEST(TestEnvironment, GetEnvReturnsEmptyStringForNonExistentVariables) {
    Mercury::Utils::Environment env;

    std::string variable {"SomethingThatDoesNotExist"};

    bool variableNotSet = std::getenv(variable.c_str()) == nullptr;
    ASSERT_TRUE(variableNotSet);

    std::string returnedValue = env.get(variable);

    EXPECT_STREQ(returnedValue.c_str(), "");
}


INSTANTIATE_TEST_CASE_P(
    Parameterised,
    EnvironmentFixture,
    ::testing::Values(
        "StringVariableSangriaForAll",
        "StringVariableMySpaceLittlePonySpace",
        "IntVariableMinusOne",
        "IntVariableFortyTwo",
        "IntVariableZero",
        "NonExistentVariable"));


/**
 * Check that Environment.getenv() returns the expected value for a given
 * variable that is set.
 */
TEST_P(EnvironmentFixture, ParamGetEnvReturnsExpectedValue) {
    Mercury::Utils::Environment env;

    std::string returnedValue = env.get(this->variable);

    EXPECT_STREQ(returnedValue.c_str(), this->value.c_str());
}


}  // namespace test
}  // namespace Utils
}  // namespace Mercury


#endif  // TEST_UNIT_UTILS_TESTENVIRONMENT_H_
