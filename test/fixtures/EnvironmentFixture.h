/**
 * \file EnvironmentFixture.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_FIXTURES_ENVIRONMENTFIXTURE_H_
#define TEST_FIXTURES_ENVIRONMENTFIXTURE_H_


#include <gtest/gtest.h>

#include <stdlib.h>

#include <map>
#include <string>

#ifdef WIN32
#include <windows.h>
#endif  // WIN32


namespace Mercury {
namespace Utils {
namespace test {


class EnvironmentFixture :
    public ::testing::Test,
    public ::testing::WithParamInterface<std::string> {
 // NOLINT
 public:
    EnvironmentFixture():
        variables({
            {"StringVariableSangriaForAll", "SangriaForAll"},
            {"StringVariableMySpaceLittlePonySpace", "My LittlePony "},
            {"IntVariableMinusOne", "-1"},
            {"IntVariableFortyTwo", "42"},
            {"IntVariableZero", "0"},
            {"NonExistentVariable", ""}
        }) {
        // Empty constructor.
    }

 protected:
    virtual void SetUp() {
        this->initParams();

        bool variableNotSet = std::getenv(variable.c_str()) == nullptr;
        ASSERT_TRUE(variableNotSet);

// TODO: translate setenv to windows counterparts
#ifdef WIN32
        SetEnvironmentVariable(this->variable.c_str(), this->value.c_str());
#else  // WIN32
        int rv = setenv(this->variable.c_str(), this->value.c_str(), 0);
        bool setSuccessfully = rv == 0;
        ASSERT_TRUE(setSuccessfully);
#endif  // WIN32
    }

    virtual void TearDown() {
        this->initParams();

// TODO: translate unsetenv to windows counterparts
#ifndef WIN32
        int rv = unsetenv(this->variable.c_str());
        bool unsetSuccessfully = rv == 0;
        ASSERT_TRUE(unsetSuccessfully);
#endif
    }

 private:
    void initParams() {
        this->variable = this->GetParam();
        this->value = this->variables[this->variable];
    }

 protected:
    std::string variable;
    std::string value;

 private:
    std::map<std::string, std::string> variables;
};


}  // namespace test
}  // namespace Utils
}  // namespace Mercury


#endif  // TEST_FIXTURES_ENVIRONMENTFIXTURE_H_
