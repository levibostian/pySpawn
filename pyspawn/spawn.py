import _spawn
import os


def run(script, program="python3", input_args=None, input_file="", timeout=0, output_file="", append_output=False, watch_for="", header=""):
    """Run a system command.

    :param script: File to run with program argument's program.
    :type script: str.
    :param program: Command-line command to run.
    :type program: str.
    :param input_args: List of strings to send to STDIN one item of the list at a time.
    :type input_args: list.
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
    :return: int -- 0 if successful, 1 if not.
    """

    # TODO
    # make sure input_args AND input_file don't both have a value (might be best to have 2 separate functions
    # instead of doing error checking.
    # do all file handling here. open input file, send the contents to the _spawn.run. get STDOUT from _spawn.run
    # and do the output file handling here.
    if input_args is None:
        send_input = []

    output = _spawn.run(program, script)
    print(output)

    # # input file handling
    # if len(input_file) > 0:
    #     if not os.path.isfile(input_file):
    #         raise FileNotFoundError(input_file + " does not exist. Try another input_file.")
    #     else:
    #         _spawn.run(command, )

