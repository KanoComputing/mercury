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

#include "kes_dashboard_live_tiles_client/internal/ITileLoader.h"
#include "kes_dashboard_live_tiles_client/ITile.h"


namespace KESDLTC {
namespace test {

class MockDefaultTileLoader : public KESDLTC::internal::ITileLoader {
 public:  // ITileLoader Methods.
    MOCK_METHOD0(getTiles, std::list<std::shared_ptr<KESDLTC::ITile>>());
};

}  // namespace test
}  // namespace KESDLTC

#endif  // TEST_MOCKS_KES_DLT_CLI_MOCKDEFAULTTILELOADER_H_
