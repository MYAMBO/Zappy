##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## test
##

from Ai.src.getWay import get_better_way_to_resources

def test_get_better_way_to_resources():
    sorted_tiles = [[0], [2], [3, 1, 6], [7, 5], [8, 4]]
    resources = [['rock'], ['big-rock', 'apple'], ['food'], ['rock', 'food', 'apple'], ['big-rock'], ['apple', 'big-rock', 'rock'], ['food', 'apple'], ['rock', 'big-rock', 'food'], ['apple']]
    assert get_better_way_to_resources(sorted_tiles, resources, None) == ['forward', 'turn right', 'forward', 'take object']
    assert get_better_way_to_resources(sorted_tiles, resources, 'food') == ['forward', 'take object']
    resources = [['rock'], ['big-rock', 'apple'], [], ['rock', 'food', 'apple'], ['big-rock'], ['apple', 'big-rock', 'rock'], ['food', 'apple'], ['rock', 'big-rock', 'food'], ['apple']]
    assert get_better_way_to_resources(sorted_tiles, resources, 'food') == ['forward', 'turn right', 'forward', 'take object']
    assert get_better_way_to_resources(sorted_tiles, resources, 'gold') == None
    sorted_tiles = [[0], [2], [3, 1, 6], [7, 5], [4]]
    assert get_better_way_to_resources(sorted_tiles, resources, 'food') == None
    sorted_tiles = [[0], [2], [3, 1, 6], [7, 5], [8, 4]]
    resources = []
    assert get_better_way_to_resources(sorted_tiles, resources, 'food') == None
