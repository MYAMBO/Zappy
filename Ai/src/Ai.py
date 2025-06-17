##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Ai
##

from Logger import logger, Output

class Ai:
    def __init__(self):
        self.__id = 0
        self.__view = None
        self.__is_first = False
        self.__inventory = {"sibur" : 0, "phiras" : 0, "thystame" : 0, "mendiane" : 0, "linemate" : 0, "deraumere" : 0}
        self.__unused_slots = 0
        self.__ai_to_follow = None
        self.__team_inventory = {}

    def set_id(self, id):
        self.__id = id

    def set_view(self, view):
        self.__view = view

    def set_is_first(self, is_first):
        self.__is_first = is_first

    def set_inventory(self, inventory):
        self.__inventory = inventory

    def set_unused_slots(self, unused_slots):
        self.__unused_slots = unused_slots

    def set_ai_to_follow(self, id):
        self.__ai_to_follow = id

    def add_in_team_inventory(self, id, inventory):
        self.__team_inventory[id] = inventory

    def team_inventory_is_ready(self):
        sibur = 0
        phiras = 0
        thystame = 0
        mendiane = 0
        linemate = 0
        deraumere = 0
        for _, value in self.__team_inventory.items():
            sibur += value["sibur"]
            phiras += value["phiras"]
            thystame += value["thystame"]
            mendiane += value["mendiane"]
            linemate += value["linemate"]
            deraumere += value["deraumere"]
        sibur += self.__inventory["sibur"]
        sibur += self.__inventory["phiras"]
        sibur += self.__inventory["thystame"]
        sibur += self.__inventory["mendiane"]
        sibur += self.__inventory["linemate"]
        sibur += self.__inventory["deraumere"]
        logger.info("global inventory : sibur : " +
                    str(sibur) + ", phiras : " +
                    str(phiras) + ", thystame : " +
                    str(thystame) + ", mendiane : " +
                    str(mendiane) + ", linemate : " +
                    str(linemate) + ", deraumere : " +
                    str(deraumere), Output.BOTH)
        if sibur < 10:
            return False
        if phiras < 6:
            return False
        if thystame < 1:
            return False
        if mendiane < 5:
            return False
        if linemate < 9:
            return False
        if deraumere < 8:
            return False
        return True

    def get_id(self):
        return self.__id

    def get_view(self):
        return self.__view

    def get_is_first(self):
        return self.__is_first

    def get_inventory(self):
        return self.__inventory

    def get_unused_slots(self):
        return self.__unused_slots
