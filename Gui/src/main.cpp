/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** main
*/

#include "Scene.hpp"
#include "Logger.hpp"

int strcmp(const std::string& string1, const std::string& string2)
{
    return (string1 == string2);
}

int main(int argc, char **argv)
{
    Debug::ClearLogFile();

    std::string port;
    std::string hostname;

    if (argc != 5) {
        std::cerr << "Wrong number of parameter" << std::endl;
        return 84;
    }

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-p" && i + 1 < argc) {
            port = argv[++i];
        } else if (std::string(argv[i]) == "-h" && i + 1 < argc) {
            hostname = argv[++i];
        } else {
            std::cerr << "Wrong parameter" << std::endl;
            return 84;
        }
    }

    try {
        gui::Scene scene(hostname, port);

        while (scene.isOpen()) {
            scene.update();
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}