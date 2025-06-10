##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Ai
##

import json
from Ai.src.Debug import logger, Output

def handle_look_string(string):
    return [obj.strip().split(' ') for obj in [tile.strip() for tile in string.strip()[1:-1].strip().split(',')]]


def handle_inventory_string(string):
    result = {}
    elt = [obj.strip() for obj in string.strip()[1:-1].split(',')]
    for item in elt:
        name, num_str = item.rsplit(' ', 1)
        result[name.strip()] = int(num_str)
    return result


def handle_command(command, reply, ai):
    if (reply == "ko\n" or reply == "ok\n"):
        return
    if (command == "Look"):
        ai.set_view(handle_look_string(reply))
        logger.info("I see this: " + json.dumps(ai.get_view()), Output.BOTH, True)
        return
    if (command == "Connect_nbr"):
        ai.set_unused_slots(int(reply))
    if (command == "Inventory"):
        ai.set_inventory(handle_inventory_string(reply))
        logger.info("I have this: " + json.dumps(ai.get_inventory()), Output.BOTH, True)
        return
