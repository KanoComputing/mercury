/**
 * \file kw.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     Provides common functions to interact with Kano World Services network APIs
 *
 */

#ifndef MERCURY_KW_H
#define MERCURY_KW_H

#include <string>
using std::string;

/**
 * \class KanoWorld
 * \brief Provides access to Kano World Services Network API
 */
class KanoWorld
{
 public:
    /**
     * \brief Sets the system wallpaper.
     */
    bool renew_token(string token);
    bool is_user_logged_in(string username);
    bool who_am_i(void);
};

#endif  // MERCURY_KW_H
