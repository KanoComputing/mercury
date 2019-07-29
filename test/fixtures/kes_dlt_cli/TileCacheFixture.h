/**
 * \file TileCacheFixture.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_FIXTURES_KES_DLT_CLI_TILECACHEFIXTURE_H_
#define TEST_FIXTURES_KES_DLT_CLI_TILECACHEFIXTURE_H_


#include <gtest/gtest.h>
#include <parson.h>

#include <stdlib.h>

#include <fstream>
#include <memory>
#include <string>

#include "mercury/config.h"
#include "mercury/utils/Filesystem.h"

#include "test/fixtures/kes_dlt_cli/KesDltResponsesFixture.h"


using std::ofstream;
using std::shared_ptr;
using std::string;

using ::testing::Test;


class TileCacheFixture : public KesDltResponsesFixture {
 public:
    TileCacheFixture():
        cacheDir(string(CMAKE_PROJ_BASE_DIR) + "/build/test/tmp/.kes-dlt-cli"),
        cacheFile("cache.json"),
        cachePath(this->cacheDir + "/" + this->cacheFile) {
        // Empty constructor.
    }

 protected:
    virtual void SetUp() {}
    virtual void TearDown() {}

 protected:
    void initialiseCache(const string& data) const {
        create_directories(this->cacheDir);

        // TODO: Add this to mercury/utils/filesystem.
        ofstream file(this->cachePath);
        file << data;
        file.close();
    }

    void clearCache() const {
        // UGH! I know... I know...
        const string cmd = "rm -rf " + this->cacheDir;
        system(cmd.c_str());
    }

 protected:
    const string cacheDir;
    const string cacheFile;
    const string cachePath;
};

#endif  // TEST_FIXTURES_KES_DLT_CLI_TILECACHEFIXTURE_H_
