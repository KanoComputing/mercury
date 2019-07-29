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


#include <gmock/gmock.h>

#include <memory>
#include <string>

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/ITileFactory.h"

using std::shared_ptr;
using std::string;


class MockTileFactory : public ITileFactory {
 public:  // ITileFactory Methods.
    MOCK_CONST_METHOD0(create, shared_ptr<ITile>());

    /**
     * \brief Google Mock doesn't permit optional arguments so simply implement
     *        the mocked function signature and offload to the mocked
     *        implementation (create_impl)
     */
    virtual shared_ptr<ITile> create(
        const string& id, const string& cover,
        const string& title, const string& description,
        const string& username, const string& app,
        const string& openUrl, const string& fallbackUrl,
        const string& coverPath = "") const {
        // NOLINT
        return this->create_impl(
            id, cover, title, description, username, app, openUrl, fallbackUrl,
            coverPath);
    }

    MOCK_CONST_METHOD9(
        create_impl,
        shared_ptr<ITile>(
            const string& id, const string& cover,
            const string& title, const string& description,
            const string& username, const string& app,
            const string& openUrl, const string& fallbackUrl,
            const string& coverPath));
};

#endif  // TEST_MOCKS_KES_DLT_CLI_MOCKTILEFACTORY_H_
