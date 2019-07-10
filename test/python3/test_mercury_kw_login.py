#
#  test_mercury_kw_login.py - pytest module to test the Login API
#

import common_functions as cf

def test_login():
    username = 'testing_user'
    password = 'kano12345experience'

    import mercury
    m = mercury.KanoWorld()
    s = m.login(username, password, cf.HTTP_VERBOSE)
    assert (s == True)
