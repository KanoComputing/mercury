/**
 * \file test.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Main runner for all Google tests
 *
 */


#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include "theme/theme.h"

#include "kw/kw_apis.h"
#include "kw/kw_server_data.h"
#include "kw/kw_persistence.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
