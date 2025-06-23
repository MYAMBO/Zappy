/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Error.hpp
*/

#ifndef ZAPPY_ERROR_HPP
#define ZAPPY_ERROR_HPP

#include <exception>
#include <string>

class Error : public std::exception {
public:
    explicit Error(std::string  message);
    [[nodiscard]] const char* what() const noexcept override;

private:
    std::string message_;
};

#endif //ZAPPY_ERROR_HPP
