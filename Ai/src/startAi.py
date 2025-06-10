#!/usr/bin/env python3
##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## zappy_ai
##

from Ai.src.Core import core
from Ai.src.Debug import logger, Output

logger.logger_clear_log_file()
logger.logger_info(b"Start Ai", Output.BOTH, True)

name = "kayu"

returnValue = core(name)
exit(returnValue)
