##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## test_Connection
##

from Client import Client, ClientError

def test_connection():
    client = Client("a non existant server", 12345)

    try:
        client.connect()
    except ClientError as e:
        assert True
        return
    assert False
