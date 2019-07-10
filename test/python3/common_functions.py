#
#  common_functions.py
#
#  Helper functions across Python3 tests
#

import os

# Dump all HTTP traffic for failing tests
HTTP_VERBOSE=True

# Set a valid token on this file to do a real test on a Kano Kit
KANO_KIT_TOKEN_FILE = os.path.join(os.getenv('HOME'), '.kanoprofile/tracker/token')

# Return the token string from the file above
def get_token():
    if (os.path.isfile(KANO_KIT_TOKEN_FILE)):
        with open(KANO_KIT_TOKEN_FILE) as f:
            token = f.read().strip()
        return token

    return None
