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
