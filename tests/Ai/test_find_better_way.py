##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## test
##

from getWay import get_better_way_to_resources

def test_get_better_way_to_resources():
    sorted_tiles = [[0], [2], [6], [3, 1], [7, 5], [8, 4]]
    resources = [['rock'], ['big-rock', 'apple'], ['food'], ['rock', 'food', 'apple'], ['big-rock'], ['apple', 'big-rock', 'rock'], ['food', 'apple'], ['rock', 'big-rock', 'food'], ['apple']]
    assert get_better_way_to_resources(sorted_tiles, resources, None) == ['Forward', 'Right', 'Forward', 'Take rock', 'Take food', 'Take apple']
    assert get_better_way_to_resources(sorted_tiles, resources, ['food']) == ['Forward', 'Take food']
    resources = [['rock'], ['big-rock', 'apple'], [], ['rock', 'food', 'apple'], ['big-rock'], ['apple', 'big-rock', 'rock'], ['food', 'apple'], ['rock', 'big-rock', 'food'], ['apple']]
    assert get_better_way_to_resources(sorted_tiles, resources, ['food']) == ['Forward', 'Forward', 'Take food']
    assert get_better_way_to_resources(sorted_tiles, resources, None) == ['Forward', 'Right', 'Forward', 'Take rock', 'Take food', 'Take apple']
    assert get_better_way_to_resources(sorted_tiles, resources, ['gold']) == ["Right"]
    assert get_better_way_to_resources(sorted_tiles, resources, ['gold', 'apple']) == ["Forward", "Forward", "Take apple"]
    sorted_tiles = [[0], [2], [6], [3, 1], [7, 5], [4]]
    assert get_better_way_to_resources(sorted_tiles, resources, ['food']) == None
    sorted_tiles = [[0], [2], [6], [3, 1], [7, 5], [8, 4]]
    resources = []
    assert get_better_way_to_resources(sorted_tiles, resources, ['food']) == None
