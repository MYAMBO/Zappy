##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Ai
##

import json
from Logger import logger, Output

def handle_look_string(string):
    string = string.strip()
    if string[0] != '[' or string[-1] != ']':
        raise
    return [obj.strip().split(' ') for obj in [tile.strip() for tile in string[1:-1].strip().split(',')]]


def handle_inventory_string(string):
    string = string.strip()
    if string[0] != '[' or string[-1] != ']':
        raise
    result = {}
    elt = [obj.strip() for obj in string[1:-1].strip().split(',')]
    for item in elt:
        name, num_str = item.rsplit(' ', 1)
        result[name.strip()] = int(num_str)
    return result


def try_view(reply, ai):
    try:
        view = handle_look_string(reply)
        ai.set_view(view)
    except:
        return False
    logger.info("I see this: " + json.dumps(ai.get_view()), Output.BOTH, True)
    return True


def try_inventory(reply, ai):
    try:
        inventory = handle_inventory_string(reply)
        ai.set_inventory(inventory)
    except:
        return False
    logger.info("I have this: " + json.dumps(ai.get_inventory()), Output.BOTH, True)
    return True


def try_connect(reply, ai):
    try:
        ai.set_unused_slots(int(reply))
    except:
        return False
    return True


def handle_follow(ai, reply):
    _, id = reply.strip()[0:-1].rsplit(';')
    ai.set_ai_to_follow(id)
    start, _ = reply.rsplit(',')
    ai.set_tile_to_follow(int(start.split("message ")[1]))


def handle_reply(reply, ai, command, name):
    if "follow me !;" in reply:
        handle_follow(ai, reply)
        return False
    if "hey_je_suis_:" in reply:
        _, id = reply.rsplit(':', 1)
        ai.add_in_team_inventory(id, {"sibur" : 0, "phiras" : 0, "thystame" : 0, "mendiane" : 0, "linemate" : 0, "deraumere" : 0})
    if reply.startswith("message ") and "j'ai ça :" in reply:
        _, info = reply.rsplit(":")
        id, inventory = info.rsplit(";")
        try:
            ai.add_in_team_inventory(id, handle_inventory_string(inventory.strip()[0:-1]))
        except:
            return False
    if command == name:
        return True
    elif reply == "ok\n":
        if command.startswith("Take "):
            ai.add_object_to_inventory(command.split(' ')[1])
        elif command.startswith("Set "):
            ai.set_down_object_from_inventory(command.split(' ')[1])
        return True
    elif reply == "ko\n":
        return True
    elif try_inventory(reply, ai) == True:
        return True
    if try_view(reply, ai) == True:
        return True
    if try_connect(reply, ai) == True:
        return True
    return False