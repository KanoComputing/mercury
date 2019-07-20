#
#  test_mercury_kw_amiloggedin.py - pytest module to test the am_i_loggedi_in API
#

import time
import json
import common_functions as cf


def fake_duration_file(filename, timestamp):
    '''
    Placeholder function which fakes a timestamp into the mercury data file
    '''
    j = json.loads(open(filename, 'r').read())
    j['duration'] = '{}'.format(timestamp)

    with open(filename, 'w') as f:
        f.write(json.dumps(j))


def test_is_logged_in_success():
    username = 'testing_user'
    password = 'kano12345experience'

    import mercury
    m = mercury.KanoWorld()
    s = m.login(username, password, cf.HTTP_VERBOSE)
    assert s is True

    s = m.is_logged_in(cf.HTTP_VERBOSE)
    assert s is True


def test_is_logged_in_fail():
    username = 'nonexisting'
    password = 'badpassword'

    import mercury
    m = mercury.KanoWorld()
    s = m.login(username, password, cf.HTTP_VERBOSE)
    assert s is False

    s = m.is_logged_in(cf.HTTP_VERBOSE)
    assert s is False


def test_timestamp_behind():
    import mercury
    m = mercury.KanoWorld()
    username = 'testing_user'
    password = 'kano12345experience'

    s = m.login(username, password, cf.HTTP_VERBOSE)
    assert s is True

    # Token expired sometime around January 1, 1970
    fake_duration_file(m.data_filename, '100')
    s = m.is_logged_in(cf.HTTP_VERBOSE)
    assert s is False


def test_timestamp_now():
    import mercury
    m = mercury.KanoWorld()

    # Token should be valid, just by 15 seconds
    fake_duration_file(m.data_filename, time.time() + 15)
    s = m.is_logged_in(cf.HTTP_VERBOSE)
    assert s is True


def test_timestamp_future():
    import mercury
    m = mercury.KanoWorld()

    # Token should be valid by 1 day
    fake_duration_file(m.data_filename, time.time() + 86400)
    s = m.is_logged_in(cf.HTTP_VERBOSE)
    assert s is True


def test_timestamp_corrupted():
    import mercury
    m = mercury.KanoWorld()

    # Token should be valid by about 1 day
    fake_duration_file(m.data_filename, 'corrupted number')
    s = m.is_logged_in(cf.HTTP_VERBOSE)
    assert s is False
