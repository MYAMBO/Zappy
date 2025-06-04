##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Core
##

from Ai.src.Client import Client, ClientError
from Ai.src.CommandHandler import handle_look_string, handle_inventory_string

def core():
    client = Client("zappy.antoiix.me", 12345)

    try:
        client.connect()
    except ClientError as e:
        print(e.message)
        return 84
    try:
        while True:
            command = input("Enter command (or 'exit' to quit): ")
            if command == "exit":
                break
            response = client.send_command("Look")
            print("Server response:", response)
    finally:
        client.close()
    return 0