#!/usr/bin/python3
#
# Python3 pytest module for the Mercury Kano World APIs
#

def test_kano_world_class():
    import mercury
    t = mercury.KanoWorld()

def test_kw_whoami():
    import mercury
    kw = mercury.KanoWorld()
    assert(kw.who_am_i() != None)
