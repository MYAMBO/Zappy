##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## test
##

from Message import follow_message

def test_follow_message():
    assert follow_message(0) == []
    assert follow_message(1) == ["Forward"]
    assert follow_message(2) == ["Forward"]
    assert follow_message(5) == ["Left", "Left", "Forward"]
    assert follow_message(6) == ["Right", "Forward"]
    assert follow_message(10) == []
