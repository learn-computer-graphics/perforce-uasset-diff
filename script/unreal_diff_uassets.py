import time
import sys
import ctypes
from dependencies import remote_execution

def execute_command_remote(command: str):
    remote_exec = remote_execution.RemoteExecution()
    remote_exec.start()

    retryCount = 0
    while len(remote_exec.remote_nodes) == 0:
        if retryCount > 15:
            ctypes.windll.user32.MessageBoxW(0, u"Failed to connect to a running unreal instance after 15 retries", u"Error running .uasset diff", 0)
            remote_exec.stop()
            return
        else:
            retryCount += 1
            time.sleep(0.1)

    remote_exec.open_command_connection(remote_exec.remote_nodes)
    remote_exec.run_command(f'unreal.SystemLibrary.execute_console_command(None, "{command}")', exec_mode=remote_execution.MODE_EXEC_STATEMENT)
    remote_exec.stop()

if len(sys.argv) != 3:
    ctypes.windll.user32.MessageBoxW(0, u"Missing arguments, you need to launch the script like 'unreal_diff_uassets.py path1.uasset path2.uasset'", u"Error running .uasset diff", 0)
    exit()

arg1 = sys.argv[1].replace("\\", "\\\\")
arg2 = sys.argv[2].replace("\\", "\\\\")
execute_command_remote(f"diff.uasset {arg1} {arg2}")
