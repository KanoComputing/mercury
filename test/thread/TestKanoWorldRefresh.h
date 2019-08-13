/**
 * \file TestKanoWorldRefresh.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Tests for the Mercury::KW - Kano World - functions
 *
 */

#ifndef TEST_THREAD_TESTKANOWORLDREFRESH_H_
#define TEST_THREAD_TESTKANOWORLDREFRESH_H_

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


using testing::Eq;


void random_delay(int max_time) {
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, max_time);

    int delay = distribution(generator);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}


TEST(KWRefreshThread, RefreshVerified) {
    Mercury::KanoWorld::KanoWorld kw;
    std::thread refresh_thr(
        &Mercury::KanoWorld::KanoWorld::refresh_account_verified,
        &kw,
        false);

    kw.get_account_verified();
    refresh_thr.join();
}


TEST(KWRefreshThread, MultiRefreshVerified) {
    int thread_count = 50;
    Mercury::KanoWorld::KanoWorld kw;
    std::vector<std::thread> threads;

    for (int i = 0; i < thread_count; i++) {
        std::thread refresh_thr(
            &Mercury::KanoWorld::KanoWorld::refresh_account_verified,
            &kw,
            false);
        threads.push_back(std::move(refresh_thr));
    }

    for (int i = 0; i < thread_count; i++) {
        std::thread read_thr(
            &Mercury::KanoWorld::KanoWorld::get_account_verified,
            &kw);
        threads.push_back(std::move(read_thr));
    }

    for (std::thread &thr : threads) {
        thr.join();
    }
}


TEST(KWReadWriteThread, ReadAndWriteTokenFromThreads) {
    int thread_count = 50;
    std::string token = "testtoken";
    Mercury::KanoWorld::KanoWorld kw;
    std::vector<std::thread> threads;

    for (int i = 0; i < thread_count; i++) {
        std::thread write_thr([token, &kw]() {
            random_delay(1000);
            kw.set_token(token);
        });
        threads.push_back(std::move(write_thr));
    }

    for (int i = 0; i < thread_count; i++) {
        std::thread read_thr([&kw]() {
            random_delay(1000);
            kw.get_token();
        });
        threads.push_back(std::move(read_thr));
    }

    for (std::thread &thr : threads) {
        thr.join();
    }
}

#endif  // TEST_THREAD_TESTKANOWORLDREFRESH_H_
