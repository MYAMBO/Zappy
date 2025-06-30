##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## AiConnection
##

import socket

class ClientError(Exception):
    def __init__(self, message):
        super().__init__(message)
        self.message = message


class Client:
    def __init__(self, host, port):
        self.__host = host
        self.__port = port
        self.__sock = None
        self.__reply_buffer = []

    def connect(self):
        self.__sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__sock.settimeout(5)
        try:
            self.__sock.connect((self.__host, self.__port))
        except socket.timeout:
            raise ClientError("timeout")
        except socket.error as e:
            raise ClientError("Socket error: " + e.strerror)
        print("Connected to " + str(self.__host) + ' ' + str(self.__port))
        print(self.__sock.recv(4096).decode())
        self.__sock.settimeout(None)

    def send_command(self, command):
        if self.__sock:
            try:
                self.__sock.sendall((command + "\n").encode())
            except socket.error as e:
                raise ClientError("Socket error: " + e.strerror)
        else:
            raise ConnectionError("Not connected to server")

    def wait_for_reply(self):
        if len(self.__reply_buffer) > 0:
            return self.__reply_buffer.pop(0)
        try:
            reply = self.__sock.recv(4096).decode()
        except socket.error as e:
            raise ClientError("Socket error: " + e.strerror)
        try:
            all_replies = reply.split('\n')
        except:
            return None
        for i in range(len(all_replies) - 1):
            self.__reply_buffer.append(all_replies[i] + "\n")
        if self.__reply_buffer:
            return self.__reply_buffer.pop(0)
        return None

    def close(self):
        if self.__sock:
            self.__sock.close()
            print("Connection closed")
