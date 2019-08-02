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

#include "kes_dashboard_live_tiles_client/ITileManager.h"


namespace KESDLTC {
namespace test {

class MockTileManager : public ITileManager {
 public:  // ITileManager Methods.
    virtual std::list<std::shared_ptr<KESDLTC::ITile>> getTiles(bool cache = true) const {  // NOLINT
        return this->getTiles_impl(cache)
    }

    MOCK_CONST_METHOD1(
        getTiles_impl,
        std::list<std::shared_ptr<KESDLTC::ITile>>(bool cache));
};

}  // namespace test
}  // namespace KESDLTC

#endif  // TEST_MOCKS_KES_DLT_CLI_MOCKTILEMANAGER_H_
