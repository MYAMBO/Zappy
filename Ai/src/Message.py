##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Core
##

def follow_message(tile):
    way = []
    actual_tile = 0
    if tile <= 0 or tile > 8:
        return None
    if tile == 5:
        way.append("Right")
        way.append("Right")
        actual_tile = 5
    elif 3 <= tile <= 4:
        way.append("Left")
        actual_tile = 3
    elif 6 <= tile <= 7:
        way.append("Right")
        actual_tile = 7
    way.append("Forward")
    if actual_tile == 0:
        actual_tile = 1
    if tile < actual_tile or tile == 8:
        way.append("Right")
        way.append("Forward")
    elif tile > actual_tile:
        way.append("Left")
        way.append("Forward")
    return way
