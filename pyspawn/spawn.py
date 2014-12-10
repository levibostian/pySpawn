import _spawn
import os
import signal


def run_input_list(script, program="python3", input_args=None, timeout=0, output_file="", append_output=False, watch_for="", header=""):
    """Run a system command with list of strings for script STDIN.

    :param script: File to run with program argument's program.
    :type script: str.
    :param program: Command-line command to run.
    :type program: str.
    :param input_args: List of strings to send to STDIN one item of the list at a time.
    :type input_args: list.
    :param timeout: Maximum time command is able to execute before program is killed.
    :type timeout: int.
    :param output_file: Path to file used to save captured STDOUT instead of the console.
    :type output_file: str.
    :param append_output: Append STDOUT to output file. (Default-- False, overwrite contents of output file).
    :type append_output: bool.
    :param watch_for: Text to listen for in STDOUT. If text is discovered, the command is killed immediately after.
    :type watch_for: str.
    :param header: Send this text to STDOUT before the command is executed.
    :type header: str.
    :return: str -- The STDOUT captured from running script.
    """

    # Must set because of library using pipes. http://coding.derkeiler.com/Archive/Python/comp.lang.python/2004-06/3823.html
    signal.signal(signal.SIGPIPE, signal.SIG_DFL)
    # TODO
    # add an argument for max chars to read. send it to the run().
    # man malloc and look at find out how to detect when you use too much mem
    # then throw python error.

    if input_args is None:
        send_input = []
    if not isinstance(input_args, list):
        raise TypeError("input_args param needs to be type list")

    accum_outputs = ""
    arg_num = 0
    for arg in input_args:
        if not isinstance(arg, str):
            raise TypeError("input_args item number: %i not a string." % arg_num)
        output = _spawn.run(program, script, arg)
        accum_outputs += output
        arg_num += 1

    return accum_outputs


def run_input_file(script, program="python3", input_file="", timeout=0, output_file="", append_output=False, watch_for="", header=""):
    """Run a system command with line separated input file for script STDIN.

    :param script: File to run with program argument's program.
    :type script: str.
    :param program: Command-line command to run.
    :type program: str.
    :param input_file: Path to file containing lists of strings to send to STDIN.
    :type input_file: str.
    :param timeout: Maximum time command is able to execute before program is killed.
    :type timeout: int.
    :param output_file: Path to file used to save captured STDOUT instead of the console.
    :type output_file: str.
    :param append_output: Append STDOUT to output file. (Default-- False, overwrite contents of output file).
    :type append_output: bool.
    :param watch_for: Text to listen for in STDOUT. If text is discovered, the command is killed immediately after.
    :type watch_for: str.
    :param header: Send this text to STDOUT before the command is executed.
    :type header: str.
    :return: str -- The STDOUT captured from running script.
    """

    # Must set because of library using pipes. http://coding.derkeiler.com/Archive/Python/comp.lang.python/2004-06/3823.html
    signal.signal(signal.SIGPIPE, signal.SIG_DFL)
    # TODO
    # add an argument for max chars to read. send it to the run().
    # man malloc and look at find out how to detect when you use too much mem
    # then throw python error.

    if not os.path.isfile(os.path.abspath(input_file)):
        raise FileNotFoundError("input_file does not exist in path: " + os.path.abspath(input_file))

    input_file_read = open(input_file, 'r')
    accum_outputs = ""
    for line in input_file_read:
        output = _spawn.run(program, script, line)
        accum_outputs += output

    return accum_outputs