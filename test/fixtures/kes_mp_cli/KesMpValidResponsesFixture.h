/**
 * \file KesMpValidResponsesFixture.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_FIXTURES_KES_MP_CLI_KESMPVALIDRESPONSESFIXTURE_H_
#define TEST_FIXTURES_KES_MP_CLI_KESMPVALIDRESPONSESFIXTURE_H_


#include <parson.h>

#include <memory>
#include <string>

#include "test/fixtures/kes_mp_cli/KesMpResponsesFixture.h"


namespace KESMPC {
namespace test {

class KesMpValidResponsesFixture :
    public KesMpResponsesFixture,
    public ::testing::WithParamInterface<std::string> {
 // NOLINT
 public:
    virtual void SetUp() {
        this->response = this->responses[this->GetParam()];
        this->paintingCount = this->paintingCounts[this->GetParam()];
    }
    virtual void TearDown() {}

 protected:
    std::shared_ptr<JSON_Value> response;
    int paintingCount;
};

}  // namespace test
}  // namespace KESMPC

#endif  // TEST_FIXTURES_KES_MP_CLI_KESMPVALIDRESPONSESFIXTURE_H_
