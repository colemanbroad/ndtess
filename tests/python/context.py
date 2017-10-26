import os
import sys

package_home = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
test_resources = os.path.join(package_home, 'test_resources/')
sys.path.insert(0, package_home)

import src