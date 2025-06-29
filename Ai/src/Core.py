##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Core
##

from Ai import Ai
from Client import *
from CommandHandler import *
from Logger import logger, Output

def init(port, machine):
    client = Client(machine, port)
    try:
        client.connect()
    except ClientError as e:
        logger.warning(e.message, Output.BOTH)
        return None
    return client


def core(name, port, machine):
    client = init(port, machine)

    if client == None:
        return 84
    ai = Ai(name, client)
    while True:
        ai.update_commands_queue()
        if not ai._Ai__commands_queue:
            ai.emergency_unfreeze()
        if not ai.send_command():
            return 84
        reply = None
        while reply is None:
            reply = ai.handle_command()
            if reply == "dead" or reply is None:
                return 0
            if not ai.handle_reply(reply):
                reply = None