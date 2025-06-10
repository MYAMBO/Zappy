##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Core
##

from Ai.src.Ai import Ai
from Ai.src.Client import *
from Ai.src.CommandHandler import *
from Ai.src.Debug import logger, Output
from Ai.src.getWay import get_better_way_to_resources
from Ai.src.SortTiles import get_visible_tiles_sorted_by_distance

def init():
    client = Client("127.0.0.1", 12345)
    try:
        client.connect()
    except ClientError as e:
        print(e.message)
        return None
    return client


def update_command_list(currentList, ai):
    if len(currentList) == 0:
        view = ai.get_view()
        if view == None:
            return currentList
        currentList = get_better_way_to_resources(get_visible_tiles_sorted_by_distance(list(range(len(view)))), view, None)
        currentList.append("Look")
        if (currentList[0] == "Look"):
            currentList[0] = "Forward"
            currentList.append("Look")
    return currentList

 
def core(name):
    fail = 0
    ai = Ai()
    client = init()
    commandToReply = None
    commands = [name, "Inventory", "Look"]

    if client == None:
        return 84
    while True:
        commands = update_command_list(commands, ai)
        if len(commands) == 0:
            continue
        commandToReply = commands.pop(0)
        try:
            client.send_command(commandToReply)
            fail = 0
        except ClientError as e:
            logger.warning(e.message)
            fail += 1
            if fail == 10:
                return 84
            continue
        logger.info("command: \"" + commandToReply + "\" has been send", Output.BOTH, True)
        logger.info(f"other commands to do after: {", ".join(commands)}", Output.BOTH, True)
        reply = client.try_get_reply()
        while reply == None:
            reply = client.try_get_reply()
        if reply == "dead":
            client.close()
            return 0
        logger.info("reply is: " + reply[0:-1], Output.BOTH, True)
        handle_command(commandToReply, reply, ai)
