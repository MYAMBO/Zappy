##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## zappy_ai
##

import sys
from Core import core
from Logger import logger, Output
from ParsingAi import parsing_ai

logger.clear_log_file()
logger.info("Starting Zappy AI", Output.FILE_OUTPUT, True)

port, name, machine = parsing_ai(sys.argv)

returnValue = core(name, port, machine)
sys.exit(returnValue)