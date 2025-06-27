##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## find good way
##

def get_better_way(layer_len, tile, resources, actual_tile, way, direction, needed):
    if tile == actual_tile:
        if not needed:
            for elt in resources:
                if elt != "player" and elt != None:
                    way.append("Take " + elt)
            return way
        for elt in resources:
            if elt in needed:
                way.append("Take " + elt)
                resources.remove(elt)
        return way
    elif tile < actual_tile:
        if direction == "nord":
            way.append("Left")
        elif direction == "ouest":
            way.append("Forward")
            actual_tile -= 1
        return get_better_way(layer_len, tile, resources, actual_tile, way, "ouest", needed)
    elif tile <= actual_tile + (layer_len // 2):
        if direction == "nord":
            way.append("Right")
        elif direction == "est":
            way.append("Forward")
            actual_tile += 1
        return get_better_way(layer_len, tile, resources, actual_tile, way, "est", needed)
    else:
        actual_tile = actual_tile + layer_len + 1
        layer_len += 2
        way.append("Forward")
        return get_better_way(layer_len, tile, resources, actual_tile, way, direction, needed)

def check_number_of_tiles(tiles, resourcesList):
    count = 0
    for tile in tiles:
        count += len(tile)
    if count != len(resourcesList):
        return False
    return True

def get_better_way_to_resources(tiles, resourcesList, needed):
    if not check_number_of_tiles(tiles, resourcesList):
        return []
    keep = {"tile" : -1, "resources" : []}
    for tile in tiles:
        for current in tile:
            resources = resourcesList[current]
            if (needed and any(need in resources for need in needed) and keep['tile'] == -1) or \
                (not needed and len(keep['resources']) < len(resources)):
                keep['tile'] = current
                keep['resources'] = resources

    if keep['tile'] != -1:
        return get_better_way(1, keep['tile'], keep['resources'], 0, [], "nord", needed)
    return ['Right', "Forward"]
