##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## test
##

from SortTiles import get_visible_tiles_sorted_by_distance

def test_get_visible_tiles_sorted_by_distance():
    tiles = []
    assert get_visible_tiles_sorted_by_distance(tiles) == []
    tiles = list(range(9))
    assert get_visible_tiles_sorted_by_distance(tiles) == [[0], [2], [6], [3, 1], [7, 5], [8, 4]]
    tiles = list(range(12))
    assert get_visible_tiles_sorted_by_distance(tiles) == [[0], [2], [6], [3, 1], [7, 5], [8, 4]]
    tiles = list(range(16))
    assert get_visible_tiles_sorted_by_distance(tiles) == [[0], [2], [6], [3, 1, 12], [7, 5], [8, 4, 13, 11], [14, 10], [15, 9]]
