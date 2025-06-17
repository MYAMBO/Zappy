##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## test
##

from Ai.src.Message import follow_message

def test_follow_message():
    assert follow_message(0) == None
    assert follow_message(1) == ["Forward"]
    assert follow_message(2) == ["Forward", "Left", "Forward"]
    assert follow_message(5) == ["Right", "Right", "Forward"]
    assert follow_message(6) == ["Right", "Forward", "Right", "Forward"]
    assert follow_message(10) == None
