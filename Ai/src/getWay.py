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

def check_number_of_tiles(tiles, resourcesList):
    count = 0
    for tile in tiles:
        for current in tile:
            count += 1
    if count != len(resourcesList):
        return False
    return True

def get_better_way_to_resources(tiles, resourcesList, needed):
    if not check_number_of_tiles(tiles, resourcesList):
        return None
    keep = {"tile" : -1, "resources" : []}
    for tile in tiles:
        for current in tile:
            resources = resourcesList[current]
            if (needed and needed in resources and keep['tile'] == -1) or (not needed and len(keep['resources']) < len(resources)):
                keep['tile'] = current
                keep['resources'] = resources

    if keep['tile'] != -1:
        way = []
        return get_better_way(1, keep['tile'], 0, way, "nord")
    return None
