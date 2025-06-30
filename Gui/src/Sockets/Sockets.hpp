/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Sockets
*/

#ifndef ZAPPY_SOCKETS_HPP
    #define ZAPPY_SOCKETS_HPP

    #include <string>
    #include <netdb.h>
    #include <unistd.h>
    #include <stdexcept>
    #include <sys/socket.h>

namespace gui {
    class Socket {
        public:
            Socket();
            ~Socket();

            void close();
            void send(const std::string& data);
            ssize_t receive(char* buffer, size_t size, bool nonBlocking);
            void connect(const std::string& hostname, const std::string& port);
            
            int getFd() const;
            bool isConnected() const;
        private:
            int _fd;
            bool _connected;
    };
};

#endif