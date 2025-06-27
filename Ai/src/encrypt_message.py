##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## encrypt_message
##

import base64
import hashlib
from cryptography.fernet import Fernet

def get_fernet_from_team_name(team_name):
    key_bytes = hashlib.sha256(team_name.encode('utf-8')).digest()
    fernet_key = base64.urlsafe_b64encode(key_bytes)
    return Fernet(fernet_key)


def encrypt_message(team_name, data):
    fernet = get_fernet_from_team_name(team_name)
    return fernet.encrypt(data.encode()).decode()


def decrypt_message(team_name, encrypted_message):
    fernet = get_fernet_from_team_name(team_name)
    try:
        return fernet.decrypt(encrypted_message.encode()).decode()
    except Exception:
        return None