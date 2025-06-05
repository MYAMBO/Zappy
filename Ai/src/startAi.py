#!/usr/bin/env python3
##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## zappy_ai
##

import ctypes

from Ai.src.Core import core
from enum import IntEnum

class Output(IntEnum):
    CONSOLE = 0
    FILE_OUTPUT = 1
    BOTH = 2

logger = ctypes.CDLL('Debug/libLogger.so')

logger.logger_info.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_bool]
logger.logger_info.restype = ctypes.c_bool

logger.logger_info(b"Hello from C++!", Output.BOTH, True)


returnValue = core()
exit(returnValue)
