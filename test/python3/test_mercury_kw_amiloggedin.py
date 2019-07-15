#
#  test_mercury_kw_amiloggedin.py - pytest module to test the am_i_loggedi_in API
#

import common_functions as cf
import time

def test_am_i_logged_in_success():
    username = 'testing_user'
    password = 'kano12345experience'

    import mercury
    m = mercury.KanoWorld()
    s = m.login(username, password, cf.HTTP_VERBOSE)
    assert (s == True)

    s = m.am_i_logged_in(cf.HTTP_VERBOSE)
    assert (s == True)

def test_am_i_logged_in_fail():
    username = 'nonexisting'
    password = 'badpassword'

    import mercury
    m = mercury.KanoWorld()
    s = m.login(username, password, cf.HTTP_VERBOSE)
    assert (s == False)

    s = m.am_i_logged_in(cf.HTTP_VERBOSE)
    assert (s == False)
