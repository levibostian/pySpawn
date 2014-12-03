import _spawn
import signal

signal.signal(signal.SIGPIPE, signal.SIG_DFL)

outputt = _spawn.run("python3", "test.py")
print("output: " + outputt);
