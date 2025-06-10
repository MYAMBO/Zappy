##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Debug
##

import ctypes
from enum import IntEnum

class Output(IntEnum):
    CONSOLE = 0
    FILE_OUTPUT = 1
    BOTH = 2

logger = ctypes.CDLL('Debug/libLogger.so')

logger.logger_info.restype = ctypes.c_bool
logger.logger_info.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_bool]

logger.logger_clear_log_file.argtypes = []
logger.logger_clear_log_file.restype = ctypes.c_bool
