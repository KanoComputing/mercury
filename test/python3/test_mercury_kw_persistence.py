#!/usr/bin/python3
#
# Python3 pytest module for the Mercury Kano World APIs
# persistence cached data
#

import os
import common_functions as cf
    
def test_persistence_filename():
    import mercury
    m = mercury.KanoWorld()
    assert (len(m.data_filename) > 0)

def test_persistence_login():
    username = 'testing_user'
    password = 'kano12345experience'

    import mercury
    m = mercury.KanoWorld()

    if os.path.isfile(m.data_filename):
        os.unlink(m.data_filename)

    assert (os.path.isfile(m.data_filename) == False)
    s = m.login(username, password, cf.HTTP_VERBOSE)
    assert (s == True)
    assert (os.path.isfile(m.data_filename) == True)

def test_persistence_load_data():
    import mercury
    m = mercury.KanoWorld()

    assert (os.path.isfile(m.data_filename) == True)
    assert (m.load_data() == True)
    assert (len(m.token) > 0)
    assert (len(m.expiration_date) > 0)

def test_persistence_load_data_corrupt():
    import mercury
    m = mercury.KanoWorld()

    with open(m.data_filename, 'w')as f:
        f.write('ouch! corrupt data')

    assert (m.load_data() == False)
    assert (len(m.token) == 0)
    assert (len(m.expiration_date) == 0)
