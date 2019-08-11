/**
 * \file MockDefaultPaintingLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief TODO
 */


#ifndef TEST_MOCKS_KES_MP_CLI_MOCKDEFAULTPAINTINGLOADER_H_
#define TEST_MOCKS_KES_MP_CLI_MOCKDEFAULTPAINTINGLOADER_H_


#include <gmock/gmock.h>

#include <list>
#include <memory>

#include "kes_moma_picks_client/internal/IPaintingLoader.h"
#include "kes_moma_picks_client/IPainting.h"


namespace KESMPC {
namespace test {

class MockDefaultPaintingLoader : public KESMPC::internal::IPaintingLoader {
 public:  // IPaintingLoader Methods.
    MOCK_METHOD0(getPaintings, std::list<std::shared_ptr<KESMPC::IPainting>>());
};

}  // namespace test
}  // namespace KESMPC

#endif  // TEST_MOCKS_KES_MP_CLI_MOCKDEFAULTPAINTINGLOADER_H_
