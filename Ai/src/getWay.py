##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## find good way
##

def get_better_way(layer_len, tile, actual_tile, way, direction):
    if tile == actual_tile:
        way.append("take object")
        return way
    elif tile < actual_tile:
        if direction == "nord":
            way.append("turn left")
        elif direction == "ouest":
            way.append("forward")
            actual_tile -= 1
        return get_better_way(layer_len, tile, actual_tile, way, "ouest")
    elif tile <= actual_tile + (layer_len // 2):
        if direction == "nord":
            way.append("turn right")
        elif direction == "est":
            way.append("forward")
            actual_tile += 1
        return get_better_way(layer_len, tile, actual_tile, way, "est")
    else:
        actual_tile = actual_tile + layer_len + 1
        layer_len += 2
        way.append("forward")
        return get_better_way(layer_len, tile, actual_tile, way, direction)

def get_better_way_to_resources(tiles, resourcesList, needed):
    keep = {"tile" : 0, "resources" : []}
    for tile in tiles:
        for current in tile:
            resources = resourcesList[current]
            if (needed and needed in resources and len(keep['resources']) < len(resources)) or (not needed and len(keep['resources']) < len(resources)):
                keep['tile'] = current
                keep['resources'] = resources

    way = []
    print("better tile to follow:", keep['tile'], "\nwith following resources:", keep['resources'], "\nwith this way:", get_better_way(1, keep['tile'], 0, way, "nord"))

get_better_way_to_resources([[0], [2], [3, 1]], [['rock0'], ['rock1', 'food', 'big rock'], ['rock2', 'food'], ['rock3']], None)
