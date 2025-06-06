##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Core
##

from Ai.src.Client import Client, ClientError
from Ai.src.CommandHandler import handle_look_string, handle_inventory_string

def init():
    client = Client("zappy.antoiix.me", 12345)
    try:
        client.connect()
    except ClientError as e:
        print(e.message)
        return None
    return client


def check_look(reply):
    return True


def reply_correspond_to_command(command, reply):
    return True

 
def core():
    client = init()
    commandToReply = None
    canSendAnotherCommand = True

    if client == None:
        return 84
    while True:
        command = ["update the commands list"]
        if canSendAnotherCommand and command.count() != 0:
            client.send_command(command[0])
            commandToReply = command.pop(0)
            canSendAnotherCommand = False
        reply = client.try_get_reply()
        if (reply == "dead"):
            client.close()
            return 0
        if (reply_correspond_to_command(commandToReply, reply)):
            canSendAnotherCommand = True
            #handle reply


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