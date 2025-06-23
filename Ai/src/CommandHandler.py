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


def manage_trantorian_turn(dir1, dir2, command_list, i):
    if dir1 in command_list:
        i -= 1
        if command_list[i] == "Forward" and command_list[i - 1] == dir1:
            command_list.pop(i)
            command_list.pop(i - 1)
        else:
            i -= 1
            command_list.pop(i)
    elif dir2 in command_list:
        command_list.insert(i, "Forward")
    else:
        command_list.insert(i, dir2)
        command_list.insert(i + 1, "Forward")
    return command_list


def handle_eject_command(eject_command, command_list):
    try:
        tile = int(eject_command.split(' ')[1])
    except:
        print("Invalid eject command !")
        return command_list

    i = len(command_list) - 1
    while i >= 0:
        if command_list[i] == "Forward":
            break
        i -= 1
    i += 1

    if tile == 1:
        command_list.insert(0, "Forward")
    elif tile == 5:
        if command_list[0] == "Forward":
            command_list.remove("Forward")
        elif "Forward" not in command_list:
            command_list.insert(0, "Right")
            command_list.insert(1, "Right")
            command_list.insert(2, "Forward")
        else:
            command_list.insert(i, command_list[0])
            command_list.insert(i + 1, "Forward")
    else:
        if tile == 3:
            command_list = manage_trantorian_turn("Right", "Left", command_list, i)
        elif tile == 7:
            command_list = manage_trantorian_turn("Left", "Right", command_list, i)
    return command_list


def handle_reply(reply, ai, command, name, command_list):
    if reply.startswith("eject: "):
        handle_eject_command(reply, command_list)
        return False
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
        if len(ai.team_inventory) < 10 and ai.inventory['food'] > 6:
            command_list.insert(0, "Fork")
        return True
    if try_view(reply, ai) == True:
        return True
    if try_connect(reply, ai) == True:
        return True
    return False