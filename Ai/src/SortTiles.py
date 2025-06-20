##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## list
##

def get_visible_tiles_sorted_by_distance(tiles):
    if not tiles:
        return []

    length = 1
    layers = []
    try:
        while tiles:
            if length > len(tiles):
                raise Exception
            layers.append(tiles[:length])
            del tiles[:length]
            length += 2
    except Exception:
        print("\nError : wrong size for last tiles line\n")

    step = 0
    sorted_tiles = []
    while layers[-1]:
        current_step_tiles = []

        for depth in range(len(layers)):
            if depth > step or not layers[depth]:
                continue

            center_index = len(layers[depth]) // 2

            if len(layers[depth]) % 2 == 0 and (step - depth) >= 2:
                current_step_tiles.append(layers[depth].pop(center_index))
                center_index = len(layers[depth]) // 2
                current_step_tiles.append(layers[depth].pop(center_index))

            if len(layers[depth]) % 2 == 1:
                current_step_tiles.append(layers[depth].pop(center_index))

        sorted_tiles.append(current_step_tiles)
        step += 1
    return sorted_tiles
