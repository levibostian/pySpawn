import _spawn


def run(command="", send_input=None, timeout=0, output_file="", listen_for="", header=""):
    """Run a system command.

    :param command: Command-line command to run.
    :type command: str.
    :param send_input: List of strings to send to STDIN one item of the list at a time.
    :type send_input: list.
    :param timeout: Maximum time command is able to execute before program is killed.
    :type timeout: int.
    :param output_file: Path to file used to save captured STDOUT instead of the console.
    :type output_file: str.
    :param listen_for: Text to listen for in STDOUT. If text is discovered, the command is killed immediately after.
    :type listen_for: str.
    :param header: Send this text to STDOUT before the command is executed.
    :type header: str.
    :return: int -- The return code.
    """
    if send_input is None: send_input = []
    _spawn.run(command)