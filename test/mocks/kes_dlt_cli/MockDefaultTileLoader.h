/**
 * \file MockDefaultTileLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief TODO
 */


#ifndef TEST_MOCKS_KES_DLT_CLI_MOCKDEFAULTTILELOADER_H_
#define TEST_MOCKS_KES_DLT_CLI_MOCKDEFAULTTILELOADER_H_


#include <gmock/gmock.h>

#include <list>
#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileLoader.h"

using std::list;
using std::shared_ptr;
using std::string;


class MockDefaultTileLoader : public ITileLoader {
 public:  // ITileLoader Methods.
    MOCK_METHOD0(getTiles, list<shared_ptr<ITile>>());
};

#endif  // TEST_MOCKS_KES_DLT_CLI_MOCKDEFAULTTILELOADER_H_
