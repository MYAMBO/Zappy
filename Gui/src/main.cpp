/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** main
*/

#include "Scene.hpp"
#include "Client.hpp"
#include "Logger.hpp"

int strcmp(const std::string& string1, const std::string& string2)
{
    return (string1 == string2);
}

int main(int argc, char **argv)
{
    Debug::DebugLog("Here ?");
    std::string port;
    std::string hostname;

    if (argc != 1 && argc != 5) {
        std::cerr << "Wrong number of parameter" << std::endl;
        return 84;
    }

    if (argc == 1) {
        hostname = "zappy.antuiix.me";
        port = "12345";
    } else {
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
    }

    std::cout << hostname << std::endl;

    gui::Scene scene;

    gui::Client::getInstance().setHostname(hostname);
    gui::Client::getInstance().setPort(port);

    while (scene.isOpen()) {
        scene.update();
    }
    return 0;
}