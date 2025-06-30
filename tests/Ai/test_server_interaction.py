##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## test_server_interaction
##

import pytest
from Ai import Ai
from Client import ClientError

class DummyClient:
    def __init__(self):
        self.commands_sent = []
        self.responses = []
        self.closed = False

    def send_command(self, command):
        if command == "crash":
            raise ClientError("Simulated crash")
        self.commands_sent.append(command)

    def wait_for_reply(self):
        if self.responses:
            return self.responses.pop(0)
        return "ok\n"

    def close(self):
        self.closed = True

@pytest.fixture
def dummy_ai():
    return Ai("team", DummyClient())

def test_send_invalid_command(dummy_ai):
    dummy_ai._Ai__commands_queue = ["crash"]
    dummy_ai.send_command()
    assert not dummy_ai._Ai__client.closed

def test_handle_bad_reply_format(dummy_ai):
    assert dummy_ai.handle_reply("") is False

def test_handle_malformed_inventory(dummy_ai):
    bad_msg = 'message 1, ' + 'j\'ai \u00e7a :id;bad_inventory_format"'
    dummy_ai.handle_reply(bad_msg)
    assert True

def test_handle_invalid_message(dummy_ai):
    bad_msg = 'message 1, "badmessageformat"'
    dummy_ai.handle_reply(bad_msg)
    assert True

def test_ko_reply_on_take(dummy_ai):
    dummy_ai._Ai__command_to_reply = "Take food"
    dummy_ai._Ai__ai_to_follow = "some-id"
    dummy_ai._Ai__is_guard = False
    assert dummy_ai.handle_reply("ko\n")

def test_ok_set_command(dummy_ai):
    dummy_ai._Ai__command_to_reply = "Set food"
    dummy_ai._Ai__inventory["food"] = 1
    dummy_ai.handle_reply("ok\n")
    assert dummy_ai._Ai__inventory["food"] == 0

def test_unknown_message_type(dummy_ai):
    dummy_ai.handle_reply("some random message")
    assert True


malformed_commands = [
    "Take",
    "Set",
    "Forward 1",
    "Left left",
    "Broadcast",
    "Broadcast Hello!",
    "Broadcast \"Unclosed string",
    "Take stone; DROP",
    "Incantation NOW!",
    "Eat food",
    "crash",
    "",
    "   ",
    "\n",
    "\x00\x01",
]

malformed_replies = [
    "dead",
    "ko",
    "ok\nko",
    "Current level:",
    "message",
    "message 1",
    "message 1, ",
    "message 1, Unquoted string",
    "message 1, \"",
    "eject: "
    "eject: x y z",
    "42",
    "team\n"
    "3 4 5\n",
    "okko",
    None,                        ]


import pytest
@pytest.mark.parametrize("command", malformed_commands)
def test_invalid_commands_do_not_crash(dummy_ai, command):
    dummy_ai._Ai__commands_queue = [command]
    try:
        dummy_ai.send_command()
    except Exception as e:
        pytest.fail(f"Command '{command}' caused crash: {e}")

@pytest.mark.parametrize("reply", malformed_replies)
def test_invalid_replies_do_not_crash(dummy_ai, reply):
    dummy_ai._Ai__command_to_reply = "team"
    try:
        dummy_ai.handle_reply(reply)
    except Exception as e:
        pytest.fail(f"Reply '{reply}' caused crash: {e}")

team_replies = [
    "",
    "8",
    "ko",
    "8 8",
    "8,8",
    "dead",
    "8 8 8",
    "8 8\n",
    "eight eight",
]

look_replies = [
    "[]",
    "123",
    "look",
    "null",
    "[", "]",
    "[player, food",
    "player, food]",
    "[player, food, food]",
]

inventory_replies = [
    "{}",
    "ok",
    "{1 2}",
    "{food}",
    "Inventory",
    "{food 1, linemate 2}",
]

okko_replies = [
    "",
    "ok",
    "ko",
    "OK",
    "okko",
    "ok ok",
    "ok\nko",
]

eject_replies = [
    "ok",
    "eject:",
    "eject: 1 2",
    "eject: 1 2 3",
    "eject: a b c",
    "eject: 1 2 3 4",
]

incantation_replies = [
    "2",
    "ok",
    "ko",
    "incant",
    "Current level: 2",
    "Current level: ",
    "current level: 2",
]

reply_cases = {
    "team": [...],
    "Look": [...],
    "Inventory": [...],
    "Broadcast": [...],
    "Forward": [...],
    "Right": [...],
    "Left": [...],
    "Take": [...],
    "Set": [...],
    "Eject": [...],
    "Incantation": [...],
}

@pytest.mark.parametrize("command, reply", [
    (cmd, r) for cmd, replies in reply_cases.items() for r in replies
])
def test_handle_all_command_to_reply_formats(dummy_ai, command, reply):
    dummy_ai._Ai__command_to_reply = command
    try:
        dummy_ai.handle_reply(reply)
    except Exception as e:
        pytest.fail(f"command='{command}', reply='{reply}' crashed with: {e}")
