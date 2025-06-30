##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Ai
##

import uuid
from Logger import logger, Output
from Message import follow_message
from Client import ClientError, Client
from getWay import get_better_way_to_ressources
from SortTiles import get_visible_tiles_sorted_by_distance
from encrypt_message import encrypt_message, decrypt_message
from CommandHandler import handle_inventory_string, try_inventory, try_view, try_connect, handle_eject_command, get_droping_items_commands, get_inventory_string

class Ai:
    def __init__(self, team_name: str, client: Client):
        self.__view = None
        self.__ready_id = []
        self.__map_size = None
        self.__client = client
        self.__unused_slots = 0
        self.__is_ready = False
        self.__is_guard = False
        self.__id = uuid.uuid4()
        self.__mates_to_wait = 0
        self.__follow_counter = 0
        self.__is_in_place = False
        self.__ai_to_follow = None
        self.__team_inventory = {}
        self.__time_for_food = 126
        self.__nb_guard_in_place = 0
        self.__team_name = team_name
        self.__command_to_reply = None
        self.__send_inventory_counter = 5
        self.__has_already_send_start = False
        self.__previous_message_guard_direction = 0
        self.__commands_queue = [team_name, "Look"]
        self.__needed_list = ["food", "sibur", "phiras", "thystame", "mendiane", "linemate", "deraumere"]
        self.__inventory = {"food" : 10, "sibur" : 0, "phiras" : 0, "thystame" : 0, "mendiane" : 0, "linemate" : 0, "deraumere" : 0}
        self.__time_by_command = {
            "Forward" : 7,
            "Right" : 7,
            "Left" : 7,
            "Look" : 7,
            "Inventory" : 1,
            "Broadcast" : 7,
            "Connect_nbr" : 0,
            "Fork" : 42,
            "Eject" : 7,
            "Take" : 7,
            "Set" : 7,
            "Incantation" : 300,
            self.__team_name : 0
        }

    def __assign_leader(self):
        self.__mates_to_wait = len(self.__team_inventory)
        self.__ai_to_follow = self.__id

    def __handle_ai_follow_logic(self):
        if self.__ai_to_follow == self.__id and self.__is_ready == False:
            if self.__mates_to_wait == 0:
                self.__start_incantation()
            elif not self.__commands_queue:
                self.__commands_queue = ["Broadcast " + encrypt_message(self.__team_name, f"\"follow me !;{self.__id}${self.__follow_counter}\"")]
                self.__follow_counter += 1
        if self.__ai_to_follow == self.__id and not self.__commands_queue:
            self.__set_command_queue_after_grouping()

    def __start_incantation(self):
        if not self.__has_already_send_start:
            self.__commands_queue.insert(0, "Broadcast " + encrypt_message(self.__team_name, "\"etttt c'est partieee !!!\""))
            self.__has_already_send_start = True
        if self.__nb_guard_in_place >= 4:
            self.__commands_queue = get_droping_items_commands(self.__inventory)
            self.__is_ready = True
            self.__commands_queue.append("Incantation")
            self.__mates_to_wait = len(self.__team_inventory)

    def __set_commands_queue_to_search_ressources(self):
        if self.__view is None:
            return
        tiles = get_visible_tiles_sorted_by_distance(list(range(len(self.__view))))
        self.__commands_queue = get_better_way_to_ressources(tiles, self.__view, self.__needed_list)
        self.__commands_queue.append("Look")

        if self.__commands_queue[0] == "Look":
            self.__commands_queue.insert(0, "Forward")
        else:
            if self.__send_inventory_counter == 5:
                self.__commands_queue.insert(0, "Broadcast " + encrypt_message(self.__team_name, f"\"j'ai ça :{self.__id};{get_inventory_string(self.__inventory)}\""))
                self.__send_inventory_counter = 0
            else:
                self.__send_inventory_counter += 1

    def __set_guard_command_queue(self):
        if self.__id is self.__ai_to_follow:
            self.__set_command_queue_after_grouping()
            return
        keys = list(self.__team_inventory.keys())
        keys.append(str(self.__id))
        keys.sort()
        was_empty = False
        if not self.__commands_queue:
            was_empty = True
        if str(self.__ai_to_follow) == keys[self.__nb_guard_in_place]:
            self.__nb_guard_in_place += 1
        if str(self.__id) == keys[self.__nb_guard_in_place] and not self.__is_in_place:
            self.__is_in_place = True
            if self.__previous_message_guard_direction == 1:
                self.__commands_queue.append("Right")
            elif self.__previous_message_guard_direction == 5:
                self.__commands_queue.append("Left")
            elif self.__previous_message_guard_direction == 7:
                self.__commands_queue.append("Right")
                self.__commands_queue.append("Right")
            self.__commands_queue.append("Forward")
            self.__commands_queue.append("Broadcast " + encrypt_message(self.__team_name, "guard in place " + str(self.__nb_guard_in_place)))
            self.__commands_queue.append("Eject")
            if was_empty:
                self.send_command()

    def __set_command_queue_after_grouping(self):
        keys = list(self.__team_inventory.keys())
        keys.append(str(self.__id))
        keys.sort()
        stone_list = list(self.__inventory.keys())
        stone_list.remove("food")
        target = 4
        i = 0
        for key in keys:
            if str(self.__id) == key and self.__id is not self.__ai_to_follow and i < target:
                self.__is_guard = True
                break
            if str(self.__ai_to_follow) == key:
                if self.__ai_to_follow == self.__id:
                    self.__commands_queue = []
                    self.__commands_queue.append("Take " + stone_list[-1])
                    break
                target += 1
            if str(self.__id) == key and not self.__is_guard:
                self.__commands_queue = []
                self.__commands_queue.append("Take " + stone_list[keys.index(str(self.__id)) - target])
                break
            i += 1
        if self.__is_guard:
            self.__commands_queue = get_droping_items_commands(self.__inventory)
            self.__set_guard_command_queue()

    def update_commands_queue(self):
        if self.team_inventory_is_ready() and self.__ai_to_follow is None and len(self.__team_inventory) > 8:
            self.__assign_leader()

        if self.__ai_to_follow is not None and not self.__commands_queue:
            self.__handle_ai_follow_logic()
            return

        if not self.__commands_queue and self.__is_ready == False:
            self.__set_commands_queue_to_search_ressources()

    def send_command(self):
        if self.__nb_guard_in_place >= 4 and not self.__is_guard:
            self.__commands_queue = get_droping_items_commands(self.__inventory)
            if self.__id is self.__ai_to_follow:
                self.__commands_queue.append("Incantation")
        if not self.__commands_queue:
            return True
        command = self.__commands_queue.pop(0)
        try:
            self.__time_for_food -= self.__time_by_command[command.split(' ')[0]]
        except:
            return True
        if self.__time_for_food < 0:
            self.__time_for_food += 126
            self.__inventory["food"] -= 1
        try:
            self.__client.send_command(command)
        except ClientError as e:
            logger.warning(e.message, Output.BOTH)
            self.__client.close()
            return False
        logger.info(str(self.__id) + ": command: \"" + command + "\" has been send", Output.BOTH)
        logger.info(f"other commands to do after: {", ".join(self.__commands_queue)}", Output.BOTH)
        self.__command_to_reply = command
        return True

    def handle_follow(self, reply):
        id, count = reply[:-1].split(';', 1)[1].rsplit('$', 1)
        if int(count) != self.__follow_counter:
            logger.info("an enemy try to usurp our commander !", Output.BOTH)
            return
        self.__follow_counter += 1
        if (self.__ai_to_follow == self.__id and str(self.__id) < id) or self.__ai_to_follow is None:
            self.__ai_to_follow = id
        if self.__commands_queue != [] and self.__commands_queue != None:
            return
        self.__commands_queue = follow_message(int(reply.split(',', 1)[0].split("message ")[1]))
        if self.__commands_queue:
            self.__commands_queue.append("Look")
        else:
            self.__is_ready = True
            self.__commands_queue = ["Broadcast " + encrypt_message(self.__team_name, "\"" + str(self.__id) + ";en position !\"")]

    def __handle_mate_inventory(self, reply):
        id, inventory = reply.split(':', 1)[1].rsplit(';', 1)
        try:
            new_inventory = handle_inventory_string(inventory.strip()[:-1])
        except:
            return
        last_inventory = self.__team_inventory.get(id)
        if last_inventory != None:
            for key, value in new_inventory.items():
                if key != "food" and last_inventory[key] > value:
                    return
        self.__team_inventory[id] = new_inventory

    def __handle_message(self, reply):
        if "follow me !;" in reply and self.__is_ready == False:
            self.handle_follow(reply)
        elif ";en position !" in reply and self.__id == self.__ai_to_follow:
            id = reply.split(';', 1)[0].split('\"', 1)[1]
            if id in self.__ready_id:
                return
            self.__mates_to_wait -= 1
            self.__ready_id.append(id)
        elif "j'ai ça :" in reply:
            self.__handle_mate_inventory(reply)
        elif "\"etttt c'est partieee !!!\"" in reply:
            self.__has_already_send_start = True
            if self.__nb_guard_in_place < 4:
                self.__set_command_queue_after_grouping()
            self.send_command()
        elif "guard in place" in reply:
            replies = reply.split(' ')
            self.__nb_guard_in_place = int(replies[-1]) + 1
            self.__previous_message_guard_direction = int(replies[1][0])
            self.__set_guard_command_queue()
            if self.__nb_guard_in_place >= 4 and not self.__is_guard:
                self.__commands_queue = get_droping_items_commands(self.__inventory)

    def handle_command(self):
        try:
            reply = self.__client.wait_for_reply()
        except ClientError as e:
            logger.warning(e.message)
            return None
        if self.__command_to_reply == self.__team_name:
            if (reply == "ko\n"):
                return None
        if not reply or reply == "":
            return None
        if reply == "dead" or (self.__command_to_reply == self.__team_name and reply == "ko\n"):
            self.__client.close()
            return None
        return reply

    def __handle_ok(self, command):
        if not self.__is_guard and self.__command_to_reply.startswith("Take ") and not self.__commands_queue and self.__ai_to_follow is not None:
            self.add_object_to_inventory(command.split(' ', 1)[1])
            self.__set_command_queue_after_grouping()
        elif command.startswith("Take "):
            self.add_object_to_inventory(command.split(' ', 1)[1])
            if len(self.__team_inventory) < 9 and self.__unused_slots == 0 and self.__inventory['food'] > 10:
                self.__commands_queue.append("Fork")
        elif command.startswith("Set "):
            self.set_down_object_from_inventory(command.split(' ', 1)[1])
        elif self.__is_guard and self.__command_to_reply == "Eject" and not self.__commands_queue:
            self.__commands_queue.append("Eject")

    def handle_reply(self, reply):
        if reply == None:
            return False
        if reply.startswith("Current level:"):
            return True
        if reply.startswith("eject: "):
            handle_eject_command(reply, self.__commands_queue)
            return False
        if reply.startswith("message "):
            try:
                start, message = reply.rsplit(", ", 1)
            except:
                return False
            decrypted_message = decrypt_message(self.__team_name, message)
            if decrypted_message is None:
                return False
            self.__handle_message(start + ", " + decrypted_message)
            return False
        command = self.__command_to_reply
        if command == self.__team_name:
            try:
                x, y = reply[:-1].split(' ', 1)
                self.__map_size = [int(x), int(y)]
                logger.info("map size is : " + str(self.__map_size), Output.BOTH)
            except:
                try:
                    self.__unused_slots = int(reply[:-1])
                except:
                    return False
                logger.info("unused slots number is : " + str(self.__unused_slots), Output.BOTH)
                return False
            return True
        if reply == "ok\n":
            self.__handle_ok(command)
            return True
        if try_inventory(reply, self):
            return True
        if reply == "Elevation underway\n" and self.__id == self.__ai_to_follow:
            self.__commands_queue = ["Incantation"]
        if reply == "ko\n":
            if command == "Incantation":
                self.__commands_queue = ["Incantation"]
            elif not self.__is_guard and self.__command_to_reply.startswith("Take ") and self.__ai_to_follow is not None:
                return True
            else:
                if not self.__has_already_send_start:
                    self.__commands_queue = ["Left", "Forward"]
            return True
        return try_view(reply, self) or try_connect(reply, self)

    def set_view(self, view):
        self.__view = view

    def set_inventory(self, inventory):
        self.__inventory = inventory

    def set_unused_slots(self, unused_slots):
        self.__unused_slots = unused_slots

    def team_inventory_is_ready(self):
        required = {
            "sibur": 10,
            "phiras": 6,
            "thystame": 1,
            "mendiane": 5,
            "linemate": 9,
            "deraumere": 8
        }
        total_inventory = {key: 0 for key in required}
        for value in self.__team_inventory.values():
            for resource in required:
                total_inventory[resource] += value.get(resource, 0)
        for resource in required:
            total_inventory[resource] += self.__inventory.get(resource, 0)
        for res, required in required.items():
            if res in self.__needed_list and total_inventory[res] >= required:
                self.__needed_list.remove(res)
        for value in self.__team_inventory.values():
            if value["food"] < 32:
                return False
        return len(self.__needed_list) == 1

    def get_view(self):
        return self.__view

    def get_inventory(self):
        return self.__inventory

    def add_object_to_inventory(self, obj):
        if obj in self.__inventory:
            self.__inventory[obj] += 1

    def set_down_object_from_inventory(self, obj):
        if obj in self.__inventory and self.__inventory[obj] > 0:
            self.__inventory[obj] -= 1
        
    def emergency_unfreeze(self):
        if not self.__commands_queue:
            if self.__has_already_send_start:
                self.__set_command_queue_after_grouping()
            else:
                self.__commands_queue = ["Look"]
            return True
        return False

    def is_a_guard(self):
        return self.__is_guard
