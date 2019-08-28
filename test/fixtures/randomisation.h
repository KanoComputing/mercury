/**
 * \file randomisation.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Functions to aid test randomisation
 *
 */


#ifndef TEST_FIXTURES_RANDOMISATION_H_
#define TEST_FIXTURES_RANDOMISATION_H_


#include <limits>
#include <random>
#include <thread>  // NOLINT


/**
 * \brief Generate a random integer between 0 and INT_MAX
 *
 * \param max    The maximum number to generate
 *
 * \returns The random integer
 */
int get_random_number(int max = std::numeric_limits<int>::max()) {
    static std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(0, max);

    return distribution(generator);
}


/**
 * \brief Sleep the current thread for a random duration up to `max_time`
 *
 * \param max_time    The maximum duration to sleep for (in milliseconds)
 */
void random_delay(int max_time) {
    int delay = get_random_number(max_time);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}


#endif  // TEST_FIXTURES_RANDOMISATION_H_
