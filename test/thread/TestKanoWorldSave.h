/**
 * \file TestKanoWorldSave.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Tests for the Mercury::KanoWorld save and load concurrency
 *
 */

#ifndef TEST_THREAD_TESTKANOWORLDSAVE_H_
#define TEST_THREAD_TESTKANOWORLDSAVE_H_

#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <chrono>  // NOLINT
#include <functional>
#include <random>
#include <string>
#include <thread>  // NOLINT
#include <utility>
#include <vector>

#include "mercury/kw/kw.h"
#include "test/fixtures/randomisation.h"


using testing::Eq;


class KWSaveThread : public Mercury::KanoWorld::KanoWorld,
                     public testing::Test {
    // Empty - bridge to protected members for unit-testing
};


/**
 * \warning Currently this only checks that we don't end up in deadlocks, in
 *          the future we would want to test that the saved data is consistent.
 *          Deadlocks will manifest themselves as these tests never terminating
 *          which needs fixing.
 */
TEST_F(KWSaveThread, ReadAndWriteDataFromThreads) {
    int thread_count = 1000;
    std::vector<std::thread> threads;

    for (int i = 0; i < thread_count; i++) {
        std::thread write_thr([&]() {
            random_delay(2000);
            this->save_data();
        });
        threads.push_back(std::move(write_thr));
    }

    for (int i = 0; i < thread_count; i++) {
        std::thread read_thr([&]() {
            random_delay(2000);
            this->load_data();
        });
        threads.push_back(std::move(read_thr));
    }

    for (const auto& thr : threads) {
        thr.join();
    }
}

#endif  // TEST_THREAD_TESTKANOWORLDSAVE_H_
