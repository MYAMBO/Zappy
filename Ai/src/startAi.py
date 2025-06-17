##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## zappy_ai
##

import sys
from Core import core
from Logger import logger, Output

logger.clear_log_file()
logger.info("Starting Zappy AI", Output.FILE_OUTPUT, True)

name = "kayu"

returnValue = core(name)
sys.exit(returnValue)