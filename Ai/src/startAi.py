#!/usr/bin/env python3
##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## zappy_ai
##

from Debug.logger import Logger, Output
from Ai.src.Core import core

logger = Logger()

logger.info("Starting Zappy AI", Output.FILE_OUTPUT, True)

returnValue = core()
exit(returnValue)
