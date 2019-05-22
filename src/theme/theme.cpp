/**
 * \file theme.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 *
 *
 */


#include <string>
using std::string;

#include "mercury/theme/theme.h"


/**
 * \warning Not implemented
 */
bool Theme::set_wallpaper(string wallpaper_path)
{
    return true;
}


/**
 * \warning Not implemented
 */
string Theme::get_wallpaper() const
{
    return "/sample/theme";
}
