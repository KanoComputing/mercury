#
#  test_mercury_kw_login.py - pytest module to test the Login API
#

import common_functions as cf

def test_login_success():
    username = 'testing_user'
    password = 'kano12345experience'

    import mercury
    m = mercury.KanoWorld()
    s = m.login(username, password, cf.HTTP_VERBOSE)
    assert (s == True)

def test_login_and_logout():
    username = 'testing_user'
    password = 'kano12345experience'

    import mercury
    m = mercury.KanoWorld()
    s = m.login(username, password, cf.HTTP_VERBOSE)
    assert (s == True)

    s = m.logout(cf.HTTP_VERBOSE)
    assert (s == True)

def test_login_failed():
    username = 'nonexisting'
    password = 'badpassword'

    import mercury
    m = mercury.KanoWorld()
    s = m.login(username, password, cf.HTTP_VERBOSE)
    assert (s == False)

    assert (len(m.token) == 0)
    assert (len(m.expiration_date) == 0)
