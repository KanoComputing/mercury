#
#  common_functions.py
#
#  Helper functions across Python3 tests
#

import os

# Dump all HTTP traffic for failing tests
HTTP_VERBOSE = True

# TODO: Change this to https://worldapi-dev.kes.kano.me when it's usable.
API_URL = 'https://worldapi-dev.kano.me'

# Set a valid token on this file to do a real test on a Kano Kit
KANO_KIT_TOKEN_FILE = os.path.join(
    os.getenv('HOME'), '.kanoprofile/tracker/token'
)


# Return the token string from the file above
def get_token():
    if (os.path.isfile(KANO_KIT_TOKEN_FILE)):
        with open(KANO_KIT_TOKEN_FILE) as f:
            token = f.read().strip()

        # Check that the token is in new API JWT format
        if len(token) > 32:
            return token

    return None
