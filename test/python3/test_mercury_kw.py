#!/usr/bin/python3
#
# Python3 pytest module for the Mercury Kano World APIs
#

import common_functions as cf
    
def test_kano_world_class():
    import mercury
    t = mercury.KanoWorld()

def test_kw_whoami():
    import mercury
    kw = mercury.KanoWorld()
    assert(kw.whoami() != None)

def test_payload_refresh_nonempty():
    import mercury
    m = mercury.KanoWorld()
    assert (m.get_refresh_header("1234567890") != None)

def test_payload_refresh_bearer():
    token = '1234567890'
    import mercury
    m = mercury.KanoWorld()
    p = m.get_refresh_header("1234567890")
    assert (p == 'Authorization: Bearer {}'.format(token))

def test_payload_refresh_kano_kit():
    token = cf.get_token()
    if token:
        import mercury
        m = mercury.KanoWorld()
        p = m.get_refresh_header(token)
        assert (p == 'Authorization: Bearer {}'.format(token))
