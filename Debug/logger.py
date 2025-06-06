##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## logger
##
import ctypes
import os
from enum import IntEnum

class Output(IntEnum):
    CONSOLE = 0
    FILE_OUTPUT = 1
    BOTH = 2

class Logger:
    def __init__(self, lib_path='Debug/libLogger.so'):
        self.enabled = os.path.isfile(lib_path)

        if self.enabled:
            self.lib = ctypes.CDLL(lib_path)

            self.lib.logger_info.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_bool]
            self.lib.logger_info.restype = ctypes.c_bool

            self.lib.logger_debug.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_bool]
            self.lib.logger_debug.restype = ctypes.c_bool

            self.lib.logger_warning.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_bool]
            self.lib.logger_warning.restype = ctypes.c_bool

            self.lib.logger_clear_log_file.argtypes = []
            self.lib.logger_clear_log_file.restype = ctypes.c_bool
        else:
            print("[Warning] Logging disabled: libLogger.so not found.")

    def info(self, message: str, output: Output = Output.CONSOLE, with_timestamp: bool = True):
        if self.enabled:
            self.lib.logger_info(message.encode(), output, with_timestamp)

    def debug(self, message: str, output: Output = Output.CONSOLE, with_timestamp: bool = True):
        if self.enabled:
            self.lib.logger_debug(message.encode(), output, with_timestamp)

    def warning(self, message: str, output: Output = Output.CONSOLE, with_timestamp: bool = True):
        if self.enabled:
            self.lib.logger_warning(message.encode(), output, with_timestamp)

    def clear_log_file(self):
        if self.enabled:
            self.lib.logger_clear_log_file()
