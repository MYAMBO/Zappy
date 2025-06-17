##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Core
##

import uuid
from Ai import Ai
from Client import *
from CommandHandler import *
from getWay import get_better_way_to_resources
from SortTiles import get_visible_tiles_sorted_by_distance

def init():
    client = Client("localhost", 12345)
    try:
        client.connect()
    except ClientError as e:
        print(e.message)
        return None
    return client


def get_inventory_string(ai):
    to_send = "["
    for key, value in ai.get_inventory().items():
        to_send += key + " " + str(value) + ", "
    to_send = to_send.removesuffix(", ")
    to_send += "]"
    return to_send


def update_command_list(currentList, ai):
    if ai.team_inventory_is_ready():
        currentList = ["Broadcast \"follow me !\""]
    if len(currentList) == 0:
        view = ai.get_view()
        if view == None:
            return currentList
        currentList = get_better_way_to_resources(get_visible_tiles_sorted_by_distance(list(range(len(view)))), view, None)
        currentList.append("Look")
        if currentList[0] == "Look":
            currentList.insert(0, "Forward")
        else:
            currentList.insert(0, "Broadcast \"j'ai ça :" + str(ai.get_id()) + ";" + get_inventory_string(ai) + "\"")
    return currentList


def handle_command(client):
    try:
        reply = client.wait_for_reply()
    except:
        return None
    if reply == "":
        return None
    logger.info("reply is: " + reply[0:-1], Output.BOTH, True)
    if reply == "dead":
        client.close()
        return None
    return reply


def core(name):
    ai = Ai()
    client = init()
    commandToReply = None
    ai.set_id(uuid.uuid4())
    commands = [name, "Broadcast \"hey_je_suis_:" + str(ai.get_id()) + "\"", "Look", "Inventory"]

    if client == None:
        return 84
    while True:
        commands = update_command_list(commands, ai)
        if len(commands) == 0:
            continue
        commandToReply = commands.pop(0)
        try:
            client.send_command(commandToReply)
        except ClientError as e:
            logger.warning(e.message, Output.BOTH)
            client.close()
            return 84
        logger.info(str(ai.get_id()) + ": command: \"" + commandToReply + "\" has been send", Output.BOTH)
        logger.info(f"other commands to do after: {", ".join(commands)}", Output.BOTH)
        reply = handle_command(client)
        if reply == None:
            return 0
        while handle_reply(reply, ai, commandToReply, name) == False:
            reply = handle_command(client)
            if reply == None:
                return 0
