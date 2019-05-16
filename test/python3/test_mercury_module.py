#!/usr/bin/python3
#
# Python3 pytest module for the Mercury library bindings
#

def test_python3():
    import sys
    assert(sys.version_info.major == 3)

def test_load_mercury():
    import mercury
