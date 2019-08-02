/**
 * \file KesDltValidResponsesFixture.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_FIXTURES_KES_DLT_CLI_KESDLTVALIDRESPONSESFIXTURE_H_
#define TEST_FIXTURES_KES_DLT_CLI_KESDLTVALIDRESPONSESFIXTURE_H_


#include <parson.h>

#include <memory>
#include <string>

#include "test/fixtures/kes_dlt_cli/KesDltResponsesFixture.h"


namespace KESDLTC {
namespace test {

class KesDltValidResponsesFixture :
    public KesDltResponsesFixture,
    public ::testing::WithParamInterface<std::string> {
 // NOLINT
 public:
    virtual void SetUp() {
        this->response = this->responses[this->GetParam()];
        this->tileCount = this->tileCounts[this->GetParam()];
    }
    virtual void TearDown() {}

 protected:
    std::shared_ptr<JSON_Value> response;
    int tileCount;
};

}  // namespace test
}  // namespace KESDLTC

#endif  // TEST_FIXTURES_KES_DLT_CLI_KESDLTVALIDRESPONSESFIXTURE_H_
