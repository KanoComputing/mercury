/**
 * \file JsonMatchers.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_MATCHERS_JSONMATCHERS_H_
#define TEST_MATCHERS_JSONMATCHERS_H_


/**
 * \brief Match an argument passed into your function as being part of a
 *        given JSON_Array*.
 */
MATCHER_P(AnyInJsonArray, jsonArray, "") {
    for (int i = 0; i < json_array_get_count(jsonArray); i++)
        if (json_value_equals(json_array_get_value(jsonArray, i), arg))
            return true;
    return false;
}

/**
 * \brief Match an argument passed into your function as being equal to a
 *        given JSON_Value*.
 */
MATCHER_P(JsonEq, jsonValue, "") {
    return json_value_equals(jsonValue, arg);
}

#endif  // TEST_MATCHERS_JSONMATCHERS_H_
