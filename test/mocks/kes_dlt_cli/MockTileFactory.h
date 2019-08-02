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

#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileFactory.h"


namespace KESDLTC {
namespace test {

class MockTileFactory : public KESDLTC::ITileFactory {
 public:  // ITileFactory Methods.
    MOCK_CONST_METHOD0(create, std::shared_ptr<KESDLTC::ITile>());

    /**
     * \brief Google Mock doesn't permit optional arguments so simply implement
     *        the mocked function signature and offload to the mocked
     *        implementation (create_impl)
     */
    virtual std::shared_ptr<KESDLTC::ITile> create(
        const std::string& id,
        const std::string& cover,
        const std::string& title,
        const std::string& description,
        const std::string& username,
        const std::string& app,
        const std::string& openUrl,
        const std::string& fallbackUrl,
        const std::string& coverPath = "") const {
        // NOLINT
        return this->create_impl(
            id, cover, title, description, username, app,
            openUrl, fallbackUrl, coverPath);
    }

    MOCK_CONST_METHOD9(
        create_impl,
        std::shared_ptr<ITile>(
            const std::string& id,
            const std::string& cover,
            const std::string& title,
            const std::string& description,
            const std::string& username,
            const std::string& app,
            const std::string& openUrl,
            const std::string& fallbackUrl,
            const std::string& coverPath));
};

}  // namespace test
}  // namespace KESDLTC

#endif  // TEST_MOCKS_KES_DLT_CLI_MOCKTILEFACTORY_H_
