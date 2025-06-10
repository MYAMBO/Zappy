##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Ai
##

class Ai:
    def __init__(self):
        self.__view = None
        self.__inventory = None
        self.__unused_slots = 0

    def set_view(self, view):
        self.__view = view

    def set_inventory(self, inventory):
        self.__inventory = inventory

    def set_unused_slots(self, unused_slots):
        self.__unused_slots = unused_slots

    def get_view(self):
        return self.__view

    def get_inventory(self):
        return self.__inventory

    def get_unused_slots(self):
        return self.__unused_slots
