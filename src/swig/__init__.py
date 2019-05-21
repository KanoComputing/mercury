#
# FIXME: the problem is: if imported from the current directory everything is fine,
# otherwise, you need to reach Theme like this: mercury._mercury.Theme
# I cannot find how to fix this yet
#

import sys
from . import mercury
sys.modules['mercury'] = __import__ ('mercury._mercury')
