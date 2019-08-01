/**
 * \file MockTileManager.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief TODO
 */


#ifndef TEST_MOCKS_KES_DLT_CLI_MOCKTILEMANAGER_H_
#define TEST_MOCKS_KES_DLT_CLI_MOCKTILEMANAGER_H_


#include <gmock/gmock.h>

#include <list>
#include <memory>

#include "mercury/kes_dashboard_live_tiles_cli/ITileManager.h"

using std::shared_ptr;


class MockTileManager : public ITileManager {
 public:  // ITileManager Methods.
    virtual list<shared_ptr<ITile>> getTiles(bool cache = true) const {
        return this->getTiles_impl(cache)
    }

    MOCK_CONST_METHOD1(getTiles_impl list<shared_ptr<ITile>>(bool cache));
};

#endif  // TEST_MOCKS_KES_DLT_CLI_MOCKTILEMANAGER_H_
