/**
 * \file TemplateTests.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_HELPERS_TEMPLATETESTS_H_
#define TEST_HELPERS_TEMPLATETESTS_H_


#include <gtest/gtest.h>

#include <memory>
#include <utility>


namespace Mercury {
namespace test {


/**
 * Templated test to check that users of a base class can use it through a
 * pointer of an interface it implements.
 */
template<class Base, class Interface, typename... Args>
void testBaseIsAnInterface(Args&&... args) {
    std::shared_ptr<Interface> sharedPointer =
        std::make_shared<Base>(std::forward<Args>(args)...);

    std::unique_ptr<Interface> uniquePointer =
        std::make_unique<Base>(std::forward<Args>(args)...);

    EXPECT_TRUE(sharedPointer != nullptr);
    EXPECT_TRUE(uniquePointer != nullptr);
}


}  // namespace test
}  // namespace Mercury


#endif  // TEST_HELPERS_TEMPLATETESTS_H_
