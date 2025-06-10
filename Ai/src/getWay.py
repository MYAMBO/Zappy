##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## find good way
##

def get_better_way(layer_len, tile, resources, actual_tile, way, direction):
    if tile == actual_tile:
        for elt in resources:
            if elt != "player":
                way.append("Take " + elt)
        return way
    elif tile < actual_tile:
        if direction == "nord":
            way.append("Left")
        elif direction == "ouest":
            way.append("Forward")
            actual_tile -= 1
        return get_better_way(layer_len, tile, resources, actual_tile, way, "ouest")
    elif tile <= actual_tile + (layer_len // 2):
        if direction == "nord":
            way.append("Right")
        elif direction == "est":
            way.append("Forward")
            actual_tile += 1
        return get_better_way(layer_len, tile, resources, actual_tile, way, "est")
    else:
        actual_tile = actual_tile + layer_len + 1
        layer_len += 2
        way.append("Forward")
        return get_better_way(layer_len, tile, resources, actual_tile, way, direction)


def get_better_way_to_resources(tiles, resourcesList, needed):
    keep = {"tile" : 0, "resources" : []}
    for tile in tiles:
        for current in tile:
            resources = resourcesList[current]
            if (needed and needed in resources and len(keep['resources']) < len(resources)) or (not needed and len(keep['resources']) < len(resources)):
                keep['tile'] = current
                keep['resources'] = resources

    way = get_better_way(1, keep['tile'], keep['resources'], 0, [], "nord")
    return way
