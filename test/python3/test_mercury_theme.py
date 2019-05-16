#!/usr/bin/python3
#
# Python3 pytest module for the Mercury theme APIs
#

def test_theme_set_wallpaper():
    from pathlib import Path
    test_wallpaper = 'data/theme/arcade_hall-1024.png'
    assert (Path(test_wallpaper).is_file() == True)

    import mercury
    t = mercury.Theme()
    assert(t.set_wallpaper(test_wallpaper) == True)

def test_theme_get_wallpaper():
    import mercury
    t = mercury.Theme()
    assert(t.get_wallpaper() != None)
