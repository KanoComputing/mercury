#!/usr/bin/python2
#
# Python2 pytest module for the Mercury library bindings
#

def test_load_mercury():
    import mercury
    assert mercury is not None

def test_load_mercury_kw():
    import mercury
    kw = mercury.KanoWorld()
    assert kw is not None

def test_login_failed():
    import mercury
    kw = mercury.KanoWorld()
    s = kw.login('abcde', '12345', False)
    assert s is False

def test_refresh_failed():
    import mercury
    kw = mercury.KanoWorld()
    s = kw.refresh_token('1234567890', False)
    assert s is False

def test_logged_in():
    import mercury
    kw = mercury.KanoWorld()
    assert kw.is_logged_in() is False
