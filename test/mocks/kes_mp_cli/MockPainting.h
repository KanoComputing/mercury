/**
 * \file MockPainting.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief TODO
 */


#ifndef TEST_MOCKS_KES_MP_CLI_MOCKPAINTING_H_
#define TEST_MOCKS_KES_MP_CLI_MOCKPAINTING_H_


#include <gmock/gmock.h>
#include <parson.h>

#include <string>

#include "kes_moma_picks_client/IPainting.h"


namespace KESMPC {
namespace test {

class MockPainting : public KESMPC::IPainting {
 public:  // ISerialisable Methods.
    MOCK_METHOD1(initialise, bool(JSON_Value* serialisedData));
    MOCK_CONST_METHOD0(serialise, JSON_Value*());

 public:  // IDownloadable Methods.
    MOCK_METHOD1(download, bool(const std::string& baseDir));

 public:  // IPainting Methods.
    MOCK_CONST_METHOD0(getId, std::string());
    MOCK_CONST_METHOD0(getCover, std::string());
    MOCK_CONST_METHOD0(getTitle, std::string());
    MOCK_CONST_METHOD0(getUsername, std::string());
    MOCK_CONST_METHOD0(getDateCreated, std::string());
    MOCK_CONST_METHOD0(getOpenUrl, std::string());
    MOCK_CONST_METHOD0(getFallbackUrl, std::string());
    MOCK_CONST_METHOD0(getCoverPath, std::string());
};

}  // namespace test
}  // namespace KESMPC

#endif  // TEST_MOCKS_KES_MP_CLI_MOCKPAINTING_H_
