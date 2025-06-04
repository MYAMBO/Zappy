##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## test
##

from Ai.src.CommandHandler import handle_look_string, handle_inventory_string

def test_handle_look_string():
    assert handle_look_string("[tile1, tile2]") == [["tile1"], ["tile2"]]
    assert handle_look_string("[rock, rock food, rock food, rock]") == [["rock"], ["rock", "food"], ["rock", "food"], ["rock"]]

def test_handle_inventory_string():
    assert handle_inventory_string("[linemate 5, sibur 0]") == {"linemate": 5, "sibur": 0}
