##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Core
##

from Ai import Ai
from Client import *
from CommandHandler import *

def init(port, machine):
    client = Client(machine, port)
    try:
        client.connect()
    except ClientError as e:
        print(e.message)
        return None
    return client


def handle_command(client):
    try:
        reply = client.wait_for_reply()
    except ClientError as e:
        logger.warning(e.message)
        return None
    if reply == "":
        return None
    logger.info("reply is: " + reply[0:-1], Output.BOTH, True)
    if reply == "dead":
        client.close()
        return None
    return reply


def core(name, port, machine):
    client = init(port, machine)
    ai = Ai(name, client)

    if client == None:
        return 84
    while True:
        ai.update_commands_queue()
        if not ai.send_command():
            return 84
        reply = handle_command(client)
        if reply == None:
            return 0
        while ai.handle_reply(reply) == False:
            reply = handle_command(client)
            if reply == None:
                return 0
