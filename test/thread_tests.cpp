/**
 * \file thread_tests.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Main runner for all Google tests
 *
 */


#include <gtest/gtest.h>

#include "thread/TestKanoWorldRefresh.h"


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
