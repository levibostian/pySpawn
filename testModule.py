import _spawn
from pyspawn import spawn
import os

_spawn.run("python3", "test.py", "levi")
spawn.run_input_list(os.path.abspath("test.py"), "python3", ["levi"])
