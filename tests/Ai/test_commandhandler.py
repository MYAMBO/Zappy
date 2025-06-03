##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## test
##

from Ai.src.AiCommandHandler import handle_look_string

def test_handle_look_string():
    assert handle_look_string("[tile1, tile2]") == ["tile1", "tile2"]
