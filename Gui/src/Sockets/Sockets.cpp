/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Sockets
*/

#include "Sockets.hpp"
#include "Logger.hpp"

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
    addrinfo hints{}, *res;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    Debug::WarningLog("Try Connection");
    int status = getaddrinfo(hostname.c_str(), port.c_str(), &hints, &res);
    if (status != 0) {
        Debug::WarningLog(gai_strerror(status));
        throw gui::HostnameError();
    }

    _fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    Debug::WarningLog("fd value : " + std::to_string(_fd));
    if (_fd < 0) {
        freeaddrinfo(res);
        Debug::WarningLog("Socket creation failed");
        throw gui::PortError();
    }

    if (::connect(_fd, res->ai_addr, res->ai_addrlen) < 0) {
        freeaddrinfo(res);
        ::close(_fd);
        _fd = -1;
        Debug::WarningLog("connection failed");
        throw gui::PortError();
    }

    freeaddrinfo(res);
    _connected = true;
    Debug::WarningLog("connection succesful");
}

void gui::Socket::send(const std::string& data)
{
    if (!_connected) {
        throw std::runtime_error("Socket not connected");
    }
    ::send(_fd, data.c_str(), data.size(), 0);
}

ssize_t gui::Socket::receive(char* buffer, size_t size, bool nonBlocking)
{
    if (!_connected) {
        throw std::runtime_error("Socket not connected");
    }
    int flags = nonBlocking ? MSG_DONTWAIT : 0;
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