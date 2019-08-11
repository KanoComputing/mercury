/**
 * \file MockPaintingCache.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief TODO
 */


#ifndef TEST_MOCKS_KES_MP_CLI_MOCKPAINTINGCACHE_H_
#define TEST_MOCKS_KES_MP_CLI_MOCKPAINTINGCACHE_H_


#include <gmock/gmock.h>

#include <list>
#include <memory>

#include "kes_moma_picks_client/internal/IPaintingCache.h"
#include "kes_moma_picks_client/IPainting.h"


namespace KESMPC {
namespace test {

class MockPaintingCache : public KESMPC::internal::IPaintingCache {
 public:  // IPaintingLoader Methods.
    MOCK_METHOD0(
        getPaintings,
        std::list<std::shared_ptr<KESMPC::IPainting>>());

 public:  // IPaintingCache Methods.
    MOCK_METHOD1(
        update,
        void(const std::list<std::shared_ptr<KESMPC::IPainting>>& paintings));
    MOCK_CONST_METHOD0(getLastUpdated, double());
    MOCK_CONST_METHOD0(isCacheEmpty, bool());
};

}  // namespace test
}  // namespace KESMPC

#endif  // TEST_MOCKS_KES_MP_CLI_MOCKPAINTINGCACHE_H_
