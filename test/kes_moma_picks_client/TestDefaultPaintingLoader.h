/**
 * \file TestDefaultPaintingLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_KES_MOMA_PICKS_CLIENT_TESTDEFAULTPAINTINGLOADER_H_
#define TEST_KES_MOMA_PICKS_CLIENT_TESTDEFAULTPAINTINGLOADER_H_


#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "kes_moma_picks_client/internal/DefaultPaintingLoader.h"
#include "kes_moma_picks_client/internal/IPaintingLoader.h"

#include "test/helpers/TemplateTests.h"
#include "test/mocks/kes_mp_cli/MockPainting.h"
#include "test/mocks/kes_mp_cli/MockPaintingFactory.h"


namespace KESMPC {
namespace test {


/**
 * Check that users of the class can use it through a pointer of its interface.
 */
TEST(TestDefaultPaintingLoader, IsAnIPaintingLoader) {
    Mercury::test::testBaseIsAnInterface<
        KESMPC::internal::DefaultPaintingLoader,
        KESMPC::internal::IPaintingLoader>();
}

/**
 * Check that DefaultPaintingLoader.getPaintings() calls
 * PaintingFactory.create() for each of the default paintings it returns.
 */
TEST(TestDefaultPaintingLoader, GetPaintingsCallsPaintingFactoryCreate) {
    auto mockPaintingFactory = std::make_shared<MockPaintingFactory>();
    auto mockPainting = std::make_shared<MockPainting>();

    KESMPC::internal::DefaultPaintingLoader
        defaultPaintingLoader(mockPaintingFactory);

    // Return the same mock Painting each for each painting data
    // from the response.
    ON_CALL(*mockPaintingFactory, create)
        .WillByDefault(::testing::Return(mockPainting));

    EXPECT_CALL(*mockPaintingFactory, create_impl)
        .Times(6);

    defaultPaintingLoader.getPaintings();
}


}  // namespace test
}  // namespace KESMPC


#endif  // TEST_KES_MOMA_PICKS_CLIENT_TESTDEFAULTPAINTINGLOADER_H_
