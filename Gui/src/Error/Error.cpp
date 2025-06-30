/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Error.cpp
*/

#include "Error.hpp"

#include <utility>

Error::Error(std::string  message)
    : message_(std::move(message))
{
}

const char* Error::what() const noexcept
{
    return message_.c_str();
}

