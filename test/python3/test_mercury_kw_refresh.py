#
#  test_mercury_kw_refresh.py - pytest module to test the refresh API
#

import common_functions as cf


def test_refresh_token_kano_kit():
    token = cf.get_token()
    if token:
        import mercury
        m = mercury.KanoWorld()
        s = m.refresh_token(token, cf.HTTP_VERBOSE)
        assert s is True


def test_refresh_token_test_user():
    token = 'eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.' \
            'eyJleHAiOjE2MTk5MjMxNjIuMDE2LCJ1c2VyIjp7ImlkIjoiMDE3MTA3Njg0NzQ4MTg5OTE0NzciLCJyb2xlcyI6W119fQ.' \
            'Dhm3_2wDUyA5Tf3IANGfB8Y6DH2Nxzgl84fPSiURdJ8'

    import mercury
    m = mercury.KanoWorld()
    s = m.refresh_token(token, cf.HTTP_VERBOSE)
    assert s is True


def test_refresh_token_nonexisting():
    import mercury
    m = mercury.KanoWorld()
    s = m.refresh_token('1234567890', cf.HTTP_VERBOSE)
    assert s is False


def test_refresh_token_empty():
    import mercury
    m = mercury.KanoWorld()
    s = m.refresh_token('', cf.HTTP_VERBOSE)
    assert s is False


def test_refresh_token_malformed():
    import mercury
    m = mercury.KanoWorld()
    s = m.refresh_token('x', cf.HTTP_VERBOSE)
    assert s is False
