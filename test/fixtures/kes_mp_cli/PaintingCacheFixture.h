/**
 * \file PaintingCacheFixture.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_FIXTURES_KES_MP_CLI_PAINTINGCACHEFIXTURE_H_
#define TEST_FIXTURES_KES_MP_CLI_PAINTINGCACHEFIXTURE_H_


#include <gtest/gtest.h>
#include <parson.h>

#include <stdlib.h>

#include <fstream>
#include <memory>
#include <string>

#include "mercury/config.h"
#include "mercury/utils/Filesystem.h"

#include "test/fixtures/kes_mp_cli/KesMpResponsesFixture.h"


namespace KESMPC {
namespace test {

class PaintingCacheFixture : public KesMpResponsesFixture {
 public:
    PaintingCacheFixture():
        cacheDir(std::string(CMAKE_PROJ_BASE_DIR) + "/build/test/tmp/.kes-mp-cli"),  // NOLINT
        cacheFile("cache.json"),
        cachePath(this->cacheDir + "/" + this->cacheFile) {
        // Empty constructor.
    }

 protected:
    virtual void SetUp() {}
    virtual void TearDown() {}

 protected:
    void initialiseCache(const std::string& data) const {
        create_directories(this->cacheDir);

        // TODO: Add this to mercury/utils/filesystem.
        std::ofstream file(this->cachePath);
        file << data;
        file.close();
    }

    void clearCache() const {
        // UGH! I know... I know...
        const std::string cmd = "rm -rf " + this->cacheDir;
        system(cmd.c_str());
    }

 protected:
    const std::string cacheDir;
    const std::string cacheFile;
    const std::string cachePath;
};

}  // namespace test
}  // namespace KESMPC

#endif  // TEST_FIXTURES_KES_MP_CLI_PAINTINGCACHEFIXTURE_H_
