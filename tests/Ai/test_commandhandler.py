##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## test
##

from Ai.src.CommandHandler import handle_look_string, handle_inventory_string, handle_eject_command

def test_handle_look_string():
    assert handle_look_string("[tile1, tile2]") == [["tile1"], ["tile2"]]
    assert handle_look_string("[rock, rock food, rock food, rock]") == [["rock"], ["rock", "food"], ["rock", "food"], ["rock"]]

def test_handle_inventory_string():
    assert handle_inventory_string("[linemate 5, sibur 0]") == {"linemate": 5, "sibur": 0}

def test_handle_eject_command():
    assert handle_eject_command("eject: 1\n", ["Forward", "Forward", "Take food"]) == ['Forward', 'Forward', 'Forward', 'Take food']
    assert handle_eject_command("eject: 1\n", ["Forward", "Forward", "Left", "Forward", "Take food"]) == ["Forward", "Forward", "Forward", "Left", "Forward", "Take food"]
    assert handle_eject_command("eject: 1\n", ["Forward", "Forward", "Left", "Forward", "Forward", "Take food"]) == ["Forward", "Forward", "Forward", "Left", "Forward", "Forward", "Take food"]
    assert handle_eject_command("eject: 1\n", ["Right", "Forward", "Take food"]) == ["Forward", "Right", "Forward", "Take food"]
    assert handle_eject_command("eject: 1\n", ["Right", "Forward", "Forward", "Take food"]) == ["Forward", "Right", "Forward", "Forward", "Take food"]
    assert handle_eject_command("eject: 1\n", ["Right", "Forward", "Take food", "Take deraumere"]) == ["Forward", "Right", "Forward", "Take food", "Take deraumere"]
    assert handle_eject_command("eject: 1\n", ["Take food"]) == ["Forward", "Take food"]

    assert handle_eject_command("eject: 5\n", ["Forward", "Forward", "Take food"]) == ['Forward', 'Take food']
    assert handle_eject_command("eject: 5\n", ["Forward", "Forward", "Left", "Forward", "Take food"]) == ["Forward", "Left", "Forward", "Take food"]
    assert handle_eject_command("eject: 5\n", ["Forward", "Forward", "Left", "Forward", "Forward", "Take food"]) == ["Forward", "Left", "Forward", "Forward", "Take food"]
    assert handle_eject_command("eject: 5\n", ["Right", "Forward", "Take food"]) == ["Right", "Forward", "Right", "Forward", "Take food"]
    assert handle_eject_command("eject: 5\n", ["Right", "Forward", "Forward", "Take food"]) == ["Right", "Forward", "Forward", "Right", "Forward", "Take food"]
    assert handle_eject_command("eject: 5\n", ["Right", "Forward", "Take food", "Take deraumere"]) == ["Right", "Forward", "Right", "Forward", "Take food", "Take deraumere"]
    assert handle_eject_command("eject: 5\n", ["Take food"]) == ["Right", "Right", "Forward", "Take food"]

    assert handle_eject_command("eject: 3\n", ["Forward", "Forward", "Take food"]) == ['Forward', 'Forward', 'Left', 'Forward', 'Take food']
    assert handle_eject_command("eject: 3\n", ["Forward", "Forward", "Left", "Forward", "Take food"]) == ["Forward", "Forward", "Left", "Forward", "Forward", "Take food"]
    assert handle_eject_command("eject: 3\n", ["Forward", "Forward", "Left", "Forward", "Forward", "Take food"]) == ["Forward", "Forward", "Left", "Forward", "Forward", "Forward", "Take food"]
    assert handle_eject_command("eject: 3\n", ["Right", "Forward", "Take food"]) == ["Take food"]
    assert handle_eject_command("eject: 3\n", ["Right", "Forward", "Forward", "Take food"]) == ["Right", "Forward", "Take food"]
    assert handle_eject_command("eject: 3\n", ["Right", "Forward", "Take food", "Take deraumere"]) == ["Take food", "Take deraumere"]
    assert handle_eject_command("eject: 3\n", ["Take food"]) == ["Left", "Forward", "Take food"]

    assert handle_eject_command("eject: 7\n", ["Forward", "Forward", "Take food"]) == ['Forward', 'Forward', 'Right', 'Forward', 'Take food']
    assert handle_eject_command("eject: 7\n", ["Forward", "Forward", "Left", "Forward", "Take food"]) == ["Forward", "Forward", "Take food"]
    assert handle_eject_command("eject: 7\n", ["Forward", "Forward", "Left", "Forward", "Forward", "Take food"]) == ["Forward", "Forward", "Left", "Forward", "Take food"]
    assert handle_eject_command("eject: 7\n", ["Right", "Forward", "Take food"]) == ["Right", "Forward", "Forward", "Take food"]
    assert handle_eject_command("eject: 7\n", ["Right", "Forward", "Forward", "Take food"]) == ["Right", "Forward", "Forward", "Forward", "Take food"]
    assert handle_eject_command("eject: 7\n", ["Right", "Forward", "Take food", "Take deraumere"]) == ["Right", "Forward", "Forward", "Take food", "Take deraumere"]
    assert handle_eject_command("eject: 7\n", ["Take food"]) == ["Right", "Forward", "Take food"]

    assert handle_eject_command("eject: 2\n", ["Forward", "Forward", "Take food"]) == ['Forward', 'Forward', 'Take food']
