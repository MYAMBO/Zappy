##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Ai
##

import uuid
from Client import *
from Logger import logger, Output
from Message import follow_message
from getWay import get_better_way_to_resources
from SortTiles import get_visible_tiles_sorted_by_distance
from CommandHandler import handle_inventory_string, try_inventory, try_view, try_connect

class Ai:
    def __init__(self, team_name, client):
        self.__id = uuid.uuid4()
        self.__view = None
        self.__client = client
        self.__unused_slots = 0
        self.__is_ready = False
        self.__mates_to_wait = 0
        self.__ai_to_follow = None
        self.__team_inventory = {}
        self.__team_name = team_name
        self.__command_to_reply = None
        self.__commands_queue = [team_name, "Look", "Inventory"]
        self.__needed_list = ["food", "sibur", "phiras", "thystame", "mendiane", "linemate", "deraumere"]
        self.__inventory = {"sibur" : 0, "phiras" : 0, "thystame" : 0, "mendiane" : 0, "linemate" : 0, "deraumere" : 0}

    def get_inventory_string(self):
        to_send = "["
        for key, value in self.__inventory.items():
            to_send += key + " " + str(value) + ", "
        to_send = to_send.removesuffix(", ")
        to_send += "]"
        return to_send

    def get_droping_items_commands(self):
        commands = []
        for name, quantity in self.__inventory.items():
            if name == "food":
                continue
            for i in range(quantity):
                commands.append("Set " + name)
        commands.append("Incantation")
        commands.append("Incantation")
        commands.append("Incantation")
        commands.append("Incantation")
        return commands

    def update_commands_queue(self):
        if self.__is_ready and self.__commands_queue == None:
            self.__commands_queue = ["Broadcast j'attend"]
            return
        if self.team_inventory_is_ready() and self.__ai_to_follow == None:
            self.__mates_to_wait = len(self.__team_inventory)
            self.__ai_to_follow = self.__id
        if self.__ai_to_follow != None and len(self.__commands_queue) == 0:
            if self.__ai_to_follow == self.__id:
                if self.__mates_to_wait == 0:
                    self.__commands_queue = self.get_droping_items_commands()
                    self.__commands_queue.insert(0, "Broadcast \"etttt c'est partieee !!!\"")
                    self.__mates_to_wait = len(self.__team_inventory)
                    return
                self.__commands_queue = ["Broadcast \"follow me !;" + str(self.__id) + "\""]
            return
        if len(self.__commands_queue) == 0:
            view = self.__view
            if view == None:
                return
            self.__commands_queue = get_better_way_to_resources(get_visible_tiles_sorted_by_distance(list(range(len(view)))), view, self.__needed_list)
            self.__commands_queue.append("Look")
            if self.__commands_queue[0] == "Look":
                self.__commands_queue.insert(0, "Forward")
            else:
                self.__commands_queue.insert(0, "Broadcast \"j'ai ça :" + str(self.__id) + ";" + self.get_inventory_string() + "\"")

    def send_command(self):
        if len(self.__commands_queue) == 0:
            return True
        commandToReply = self.__commands_queue.pop(0)
        try:
            self.__client.send_command(commandToReply)
        except ClientError as e:
            logger.warning(e.message, Output.BOTH)
            self.__client.close()
            return False
        logger.info(str(self.__id) + ": command: \"" + commandToReply + "\" has been send", Output.BOTH)
        logger.info(f"other commands to do after: {", ".join(self.__commands_queue)}", Output.BOTH)
        self.__command_to_reply = commandToReply
        return True

    def handle_follow(self, reply):
        _, id = reply.strip()[0:-1].rsplit(';')
        if self.__ai_to_follow == self.__id and str(self.__id) < id:
            self.__ai_to_follow = id
            return
        elif self.__ai_to_follow == None:
            self.__ai_to_follow = id
        if self.__ai_to_follow != id:
            return
        if self.__commands_queue == None or len(self.__commands_queue) > 0:
            return
        start, _ = reply.rsplit(',')
        self.__commands_queue = follow_message(int(start.split("message ")[1]))
        if self.__commands_queue != None:
            self.__commands_queue.append("Look")
        elif self.__is_ready == False:
            self.__is_ready = True
            self.__commands_queue = ["Broadcast \"" + str(self.__id) + ";en position !\""]

    def handle_message(self, reply):
        if "follow me !;" in reply:
            self.handle_follow(reply)
        elif ";en position !" in reply and self.__id == self.__ai_to_follow:
            self.__mates_to_wait -= 1
        elif "j'ai ça :" in reply:
            _, info = reply.rsplit(":")
            id, inventory = info.rsplit(";")
            try:
                self.__team_inventory[id] = handle_inventory_string(inventory.strip()[0:-1])
            except:
                return
        if "\"etttt c'est partieee !!!\"" in reply:
            self.__commands_queue = self.get_droping_items_commands()

    def handle_reply(self, reply):
        command = self.__command_to_reply
        if reply.startswith("message "):
            self.handle_message(reply)
            return False
        if command == self.__team_name:
            return True
        if reply == "ok\n":
            if command.startswith("Take "):
                self.add_object_to_inventory(command.split(' ')[1])
            elif command.startswith("Set "):
                self.set_down_object_from_inventory(command.split(' ')[1])
            return True
        return reply == "ko\n" or try_inventory(reply, self) or try_view(reply, self) or try_connect(reply, self)

    def set_view(self, view):
        self.__view = view

    def set_inventory(self, inventory):
        self.__inventory = inventory

    def set_unused_slots(self, unused_slots):
        self.__unused_slots = unused_slots

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
        phiras += self.__inventory["phiras"]
        thystame += self.__inventory["thystame"]
        mendiane += self.__inventory["mendiane"]
        linemate += self.__inventory["linemate"]
        deraumere += self.__inventory["deraumere"]
        logger.info("global inventory : sibur : " +
                    str(sibur) + "/10, phiras : " +
                    str(phiras) + "/6, thystame : " +
                    str(thystame) + "/1, mendiane : " +
                    str(mendiane) + "/5, linemate : " +
                    str(linemate) + "/9, deraumere : " +
                    str(deraumere) + "/8", Output.BOTH)
        if "sibur" in self.__needed_list and sibur >= 10:
            self.__needed_list.remove("sibur")
        if "phiras" in self.__needed_list and phiras >= 6:
            self.__needed_list.remove("phiras")
        if "thystame" in self.__needed_list and thystame >= 1:
            self.__needed_list.remove("thystame")
        if "mendiane" in self.__needed_list and mendiane >= 5:
            self.__needed_list.remove("mendiane")
        if "linemate" in self.__needed_list and linemate >= 9:
            self.__needed_list.remove("linemate")
        if "deraumere" in self.__needed_list and deraumere >= 8:
            self.__needed_list.remove("deraumere")
        return len(self.__needed_list) == 1

    def get_id(self):
        return self.__id

    def get_view(self):
        return self.__view

    def get_inventory(self):
        return self.__inventory

    def add_object_to_inventory(self, object):
        try:
            self.__inventory[object] += 1
        except:
            return

    def set_down_object_from_inventory(self, object):
        try:
            if self.__inventory[object] > 0:
                self.__inventory[object] -= 1
        except:
            return