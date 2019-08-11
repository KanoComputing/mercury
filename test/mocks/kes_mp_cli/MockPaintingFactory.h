/**
 * \file MockPaintingFactory.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief TODO
 */

#ifndef TEST_MOCKS_KES_MP_CLI_MOCKPAINTINGFACTORY_H_
#define TEST_MOCKS_KES_MP_CLI_MOCKPAINTINGFACTORY_H_


#include <gmock/gmock.h>

#include <memory>
#include <string>

#include "kes_moma_picks_client/IPainting.h"
#include "kes_moma_picks_client/IPaintingFactory.h"


namespace KESMPC {
namespace test {

class MockPaintingFactory : public KESMPC::IPaintingFactory {
 public:  // IPaintingFactory Methods.
    MOCK_CONST_METHOD0(create, std::shared_ptr<KESMPC::IPainting>());

    /**
     * \brief Google Mock doesn't permit optional arguments so simply implement
     *        the mocked function signature and offload to the mocked
     *        implementation (create_impl)
     */
    virtual std::shared_ptr<KESMPC::IPainting> create(
        const std::string& id,
        const std::string& cover,
        const std::string& title,
        const std::string& username,
        const std::string& dateCreated,
        const std::string& openUrl,
        const std::string& fallbackUrl,
        const std::string& coverPath = "") const {
        // NOLINT
        return this->create_impl(
            id,
            cover,
            title,
            username,
            dateCreated,
            openUrl,
            fallbackUrl,
            coverPath);
    }

    MOCK_CONST_METHOD8(
        create_impl,
        std::shared_ptr<IPainting>(
            const std::string& id,
            const std::string& cover,
            const std::string& title,
            const std::string& username,
            const std::string& dateCreated,
            const std::string& openUrl,
            const std::string& fallbackUrl,
            const std::string& coverPath));
};

}  // namespace test
}  // namespace KESMPC

#endif  // TEST_MOCKS_KES_MP_CLI_MOCKPAINTINGFACTORY_H_
