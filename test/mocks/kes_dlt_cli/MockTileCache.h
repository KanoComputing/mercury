/**
 * \file MockTileCache.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief TODO
 */


#ifndef TEST_MOCKS_KES_DLT_CLI_MOCKTILECACHE_H_
#define TEST_MOCKS_KES_DLT_CLI_MOCKTILECACHE_H_


#include <gmock/gmock.h>

#include <list>
#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileCache.h"

using std::list;
using std::shared_ptr;
using std::string;

using KESDLTC::internal::ITileCache;
using KESDLTC::ITile;


class MockTileCache : public ITileCache {
 public:  // ITileLoader Methods.
    MOCK_METHOD0(getTiles, list<shared_ptr<ITile>>());

 public:  // ITileCache Methods.
    MOCK_METHOD1(update, void(const list<shared_ptr<ITile>>& tiles));
    MOCK_CONST_METHOD0(getLastUpdated, double());
    MOCK_CONST_METHOD0(isCacheEmpty, bool());
};

#endif  // TEST_MOCKS_KES_DLT_CLI_MOCKTILECACHE_H_
