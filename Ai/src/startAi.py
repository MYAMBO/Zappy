#!/usr/bin/env python3
##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## zappy_ai
##

from Ai.src.Core import core
from Ai.src.Debug import logger, Output

logger.info("Starting Zappy AI", Output.FILE_OUTPUT, True)

name = "kayu"

returnValue = core(name)
exit(returnValue)
