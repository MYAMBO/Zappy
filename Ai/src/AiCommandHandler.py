##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Ai
##

def handle_look_string(str):
    return [elem.strip() for elem in str[1:-1].split(',')]


def handle_inventory_string(str):
    result = {}
    for item in handle_look_string(str):
        name, num_str = item.rsplit(' ', 1)
        result[name.strip()] = int(num_str)
    return result

a = handle_look_string("[tile1, tile2]")
b = handle_inventory_string("[linemate 5, sibur 0]")
print(a)
print(b)
