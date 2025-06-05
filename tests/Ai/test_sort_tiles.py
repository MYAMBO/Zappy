##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## test
##

from Ai.src.SortTiles import get_visible_tiles_sorted_by_distance

def test_get_visible_tiles_sorted_by_distance():
    tiles = []
    assert get_visible_tiles_sorted_by_distance(tiles) == []
    tiles = list(range(9))
    assert get_visible_tiles_sorted_by_distance(tiles) == [[0], [2], [3, 1, 6], [7, 5], [8, 4]]
    tiles = list(range(12))
    assert get_visible_tiles_sorted_by_distance(tiles) == [[0], [2], [3, 1, 6], [7, 5], [8, 4]]
