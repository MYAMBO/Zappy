/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Sockets
*/

#include "Sockets.hpp"
#include "Error.hpp"

gui::Socket::Socket()
    : _fd(-1), _connected(false)
{
}

gui::Socket::~Socket()
{
    close();
}

void gui::Socket::connect(const std::string& hostname, const std::string& port)
{
    addrinfo *res;
    addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(hostname.c_str(), port.c_str(), &hints, &res);
    if (status != 0) {
        throw std::runtime_error(gai_strerror(status));
    }

    _fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (_fd < 0) {
        freeaddrinfo(res);
        throw Error("Socket creation failed");
    }

    if (::connect(_fd, res->ai_addr, res->ai_addrlen) < 0) {
        freeaddrinfo(res);
        ::close(_fd);
        _fd = -1;
        throw Error("Connection failed");
    }

    freeaddrinfo(res);
    _connected = true;
}

void gui::Socket::send(const std::string& data)
{
    if (!_connected) {
        throw Error("Socket not connected");
    }
    ::send(_fd, data.c_str(), data.size(), 0);
}

ssize_t gui::Socket::receive(char* buffer, size_t size, bool nonBlocking)
{
    if (!_connected) {
        throw Error("Socket not connected");
    }
    int flags = 0;
    if (nonBlocking)
        flags = MSG_DONTWAIT;
    return recv(_fd, buffer, size, flags);
}

void gui::Socket::close()
{
    if (_fd >= 0) {
        ::close(_fd);
        _fd = -1;
        _connected = false;
    }
}

bool gui::Socket::isConnected() const
{
    return _connected;
}

int gui::Socket::getFd() const
{
    return _fd;
}