##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Core
##

def follow_message(tile):
    if tile == 0:
        return []
    elif tile == 1 or tile == 2 or tile == 8:
        return ["Forward"]
    elif tile == 3 or tile == 4:
        return ["Left", "Forward"]
    elif tile == 5:
        return ["Left", "Left", "Forward"]
    else:
        return ["Right", "Forward"]
