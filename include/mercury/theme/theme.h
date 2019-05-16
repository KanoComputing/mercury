/**
 * \file theme.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     Handles all theming for the system
 *
 */


#ifndef MERCURY_THEME_THEME_H_
#define MERCURY_THEME_THEME_H_


#include <string>
using namespace std;


/**
 * \class Theme
 * \brief Manages setting all theme elements.
 */
class Theme
{
 public:
    /**
     * \brief Sets the system wallpaper.
     */
    bool set_wallpaper(string wallpaper_path);
    string get_wallpaper() const;
};


#endif  // MERCURY_THEME_THEME_H_
