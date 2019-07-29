/**
 * \file MockTileFactory.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief TODO
 */

#ifndef TEST_MOCKS_KES_DLT_CLI_MOCKTILEFACTORY_H_
#define TEST_MOCKS_KES_DLT_CLI_MOCKTILEFACTORY_H_


#include <memory>

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/ITileFactory.h"

using std::shared_ptr;


class MockTileFactory : public ITileFactory {
 public:  // ITileFactory Methods.
    MOCK_CONST_METHOD0(create, shared_ptr<ITile>());
};

#endif  // TEST_MOCKS_KES_DLT_CLI_MOCKTILEFACTORY_H_
