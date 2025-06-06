##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Core
##

from Ai.src.Ai import Ai
from Ai.src.Client import *
from Ai.src.CommandHandler import *

def init():
    client = Client("zappy.antoiix.me", 12345)
    try:
        client.connect()
    except ClientError as e:
        print(e.message)
        return None
    return client

 
def core():
    ai = Ai()
    client = init()
    commandToReply = None
    canSendAnotherCommand = True

    if client == None:
        return 84
    while True:
        commands = ["update the commands list"]
        if canSendAnotherCommand and commands.count != 0:
            client.send_command(commands[0])
            commandToReply = commands.pop(0)
            canSendAnotherCommand = False
        reply = client.try_get_reply()
        if (reply == "dead"):
            client.close()
            return 0
        if (reply != None):
            canSendAnotherCommand = True
            handle_command(commandToReply, reply, ai)


"""
def core():
    client = init()

    if client == None:
        return 84
    try:
        while True:
            command = input("Enter command (or 'exit' to quit): ")
            if command == "exit":
                break
            client.send_command(command)
            response = client.try_get_reply()
            print("Server response:", response)
    finally:
        client.close()
    return 0
    """