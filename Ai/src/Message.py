##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Core
##

def follow_message(tile):
    if tile == 1 or tile == 2 or tile == 8:
        return ["Forward"]
    elif tile == 3 or tile == 4:
        return ["Left"]
    elif 5 <= tile <= 7:
        return ["Right"]
