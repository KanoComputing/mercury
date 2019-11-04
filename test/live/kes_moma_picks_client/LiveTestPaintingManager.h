/**
 * \file LiveTestPaintingManager.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_LIVE_KES_MOMA_PICKS_CLIENT_LIVETESTPAINTINGMANAGER_H_
#define TEST_LIVE_KES_MOMA_PICKS_CLIENT_LIVETESTPAINTINGMANAGER_H_


#include <gtest/gtest.h>

#include <stdlib.h>

#include <list>
#include <memory>
#include <string>

#include "kes_moma_picks_client/IPainting.h"
#include "kes_moma_picks_client/PaintingManager.h"

#include "mercury/config.h"


namespace KESMPC {
namespace test {

/**
 * This test actually runs live. It will perform an http request to the live
 * KES and write to the filesystem paintings. For debugging purposes only.
 */
TEST(LiveTestPaintingManager, DoesSomethingOrOther) {
    const std::string cacheDir =
        std::string(CMAKE_PROJ_BASE_DIR) + "/build/test/tmp/.kes-mp-cli";

    // Wipe cache.
    const std::string cmd = std::string("rm -rf ") + cacheDir;
    system(cmd.c_str());

    std::list<std::shared_ptr<KESMPC::IPainting>> paintings;
    KESMPC::PaintingManager paintingManager(cacheDir);

    // Download from KES.
    paintings = paintingManager.getPaintings(false);
    EXPECT_FALSE(paintings.empty());

    // Retrieve from cache (cooldown).
    paintings = paintingManager.getPaintings(false);
    EXPECT_FALSE(paintings.empty());

    // Retrieve from cache.
    paintings = paintingManager.getPaintings(true);
    EXPECT_FALSE(paintings.empty());

    // Wipe cache.
    system(cmd.c_str());

    // Get default paintings.
    paintings = paintingManager.getPaintings(true);
    EXPECT_FALSE(paintings.empty());

    // TODO: EXPECT_FALSE(exists(cacheDir + "/cache.json"));
}

}  // namespace test
}  // namespace KESMPC

#endif  // TEST_LIVE_KES_MOMA_PICKS_CLIENT_LIVETESTPAINTINGMANAGER_H_
