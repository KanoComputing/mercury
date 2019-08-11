/**
 * \file MockPaintingManager.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief TODO
 */


#ifndef TEST_MOCKS_KES_MP_CLI_MOCKPAINTINGMANAGER_H_
#define TEST_MOCKS_KES_MP_CLI_MOCKPAINTINGMANAGER_H_


#include <gmock/gmock.h>

#include <list>
#include <memory>

#include "kes_moma_picks_client/IPaintingManager.h"


namespace KESMPC {
namespace test {

class MockPaintingManager : public IPaintingManager {
 public:  // IPaintingManager Methods.
    virtual std::list<std::shared_ptr<KESMPC::IPainting>> getPaintings(bool cache = true) const {  // NOLINT
        return this->getPaintings_impl(cache)
    }

    MOCK_CONST_METHOD1(
        getPaintings_impl,
        std::list<std::shared_ptr<KESMPC::IPainting>>(bool cache));
};

}  // namespace test
}  // namespace KESMPC

#endif  // TEST_MOCKS_KES_MP_CLI_MOCKPAINTINGMANAGER_H_
