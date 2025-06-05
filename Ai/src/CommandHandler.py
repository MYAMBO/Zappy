##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Ai
##

def handle_look_string(string):
    return [obj.split(' ') for obj in [tile.strip() for tile in string[1:-1].split(',')]]


def handle_inventory_string(string):
    result = {}
    elt = [obj.strip() for obj in string[1:-1].split(',')]
    for item in elt:
        name, num_str = item.rsplit(' ', 1)
        result[name.strip()] = int(num_str)
    return result
