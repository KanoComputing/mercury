/**
 * \file MockOnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief TODO
 */


#ifndef TEST_MOCKS_KES_DLT_CLI_MOCKONLINELOADER_H_
#define TEST_MOCKS_KES_DLT_CLI_MOCKONLINELOADER_H_


#include <gmock/gmock.h>

#include <list>
#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/IOnlineLoader.h"
#include "kes_dashboard_live_tiles_client/ITile.h"

using std::list;
using std::shared_ptr;
using std::string;

using KESDLTC::internal::IOnlineLoader;
using KESDLTC::ITile;


class MockOnlineLoader : public IOnlineLoader {
 public:  // ITileLoader Methods.
    MOCK_METHOD0(getTiles, list<shared_ptr<ITile>>());

 public:  // IOnlineLoader Methods.
    MOCK_CONST_METHOD0(getQueryCooldown, double());
};

#endif  // TEST_MOCKS_KES_DLT_CLI_MOCKONLINELOADER_H_
