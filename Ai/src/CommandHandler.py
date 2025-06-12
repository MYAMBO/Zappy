##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Ai
##

import json
from Logger import logger, Output

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
    if reply == "ko\n" or reply.startswith("message"):
        return
    elif reply == "ok\n":
        if command.startswith("Take "):
            ai.add_object_to_inventory(command.split(' ')[1])
        elif command.startswith("Set "):
            ai.set_down_object_from_inventory(command.split(' ')[1])
    elif command == "Look":
        ai.set_view(handle_look_string(reply))
        logger.info("I see this: " + json.dumps(ai.get_view()), Output.BOTH, True)
    elif command == "Connect_nbr":
        ai.set_unused_slots(int(reply))
    elif command == "Inventory":
        ai.set_inventory(handle_inventory_string(reply))
        logger.info("I have this: " + json.dumps(ai.get_inventory()), Output.BOTH, True)
