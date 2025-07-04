##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Makefile
##


SERVER_SRC = 												\
				Server/src/main.c 							\
				Server/src/utils.c							\
				Server/src/garbage.c 						\
				Server/src/look_utils.c                     \
				Server/src/init_server.c 					\
                Server/src/init_player.c 					\
				Server/src/handle_event.c					\
				Server/src/init_density.c 					\
				Server/src/split_string.c 					\
				Server/src/start_server.c 					\
				Server/src/map_protocol.c   				\
				Server/src/slot_handler.c					\
				Server/src/poll_handling.c  				\
				Server/src/options_parser.c 				\
				Server/src/actions_protocol.c				\
                Server/src/handle_connection.c				\
				Server/src/command_execution.c				\
				Server/src/technical_protocol.c 			\
				Server/src/eject_communication.c            \
				Server/src/generate_ressources.c			\
				Server/src/incantation_protocol.c           \
                Server/src/commands/command_quit.c			\
				Server/src/actions_communication.c          \
				Server/src/inventory_communication.c        \
				Server/src/movements_communication.c        \
				Server/src/look_around_communication.c      \
				Server/src/incantation_communication.c      \
                Server/src/unique_connection_id_getter.c 	\
				Server/src/player_informations_protocol.c 	\
				Server/src/graphic_connect.c \
				Server/src/commands/command_pin.c	\
				Server/src/commands/command_plv.c	\
				Server/src/commands/command_ppo.c	\
				Server/src/commands/command_msz.c	\
				Server/src/commands/command_mct.c	\
				Server/src/commands/command_bct.c	\
				Server/src/commands/command_forward.c	\
				Server/src/commands/command_right.c	\
				Server/src/commands/command_left.c	\
				Server/src/commands/command_look.c	\
				Server/src/commands/command_inventory.c	\
				Server/src/commands/command_broadcast.c	\
				Server/src/commands/command_eject.c	\
				Server/src/get_signal_direction.c	\
				Server/src/time_handler.c	\
				Server/src/command_exec_handler.c	\
				Server/src/player_connection_protocol.c 	\
				Server/src/commands/command_take.c       	\
				Server/src/commands/command_drop.c       	\
				Server/src/time_unit_protocol.c				\
				Server/src/commands/command_sgt.c			\
				Server/src/commands/command_sst.c			\
				Server/src/commands/command_tna.c			\
				Server/src/commands/command_connect_nbr.c	\
				Server/src/commands/command_incantation.c	\
				Server/src/commands/command_fork.c			\
				Server/src/handle_fork_communication.c			\
				Server/src/egg_protocol.c					\
				Server/src/incantation_list.c	\
				Server/src/send_init_graphic.c	\
				Server/src/send_slots_remaining.c	\
				Server/src/time_exec_handler.c	\
				Server/src/send_slot_messages.c	\

GUI_SRC = 												\
				Gui/src/main.cpp 						\
														\
				Gui/src/Items/Food/Food.cpp 			\
				Gui/src/Items/AItem/AItem.cpp 			\
				Gui/src/Items/Sibur/Sibur.cpp			\
				Gui/src/Items/Phiras/Phiras.cpp			\
				Gui/src/Items/Mendiane/Mendiane.cpp		\
				Gui/src/Items/Thystame/Thystame.cpp		\
				Gui/src/Items/Linemate/Linemate.cpp		\
				Gui/src/Items/Deraumere/Deraumere.cpp	\
														\
				Gui/src/Egg/Egg.cpp						\
				Gui/src/Tile/Tile.cpp					\
				Gui/src/Menu/Menu.cpp					\
				Gui/src/Error/Error.cpp 				\
				Gui/src/Scene/Scene.cpp					\
				Gui/src/Client/Client.cpp 				\
				Gui/src/Button/Button.cpp 				\
				Gui/src/Player/Player.cpp				\
				Gui/src/Sockets/Sockets.cpp				\
				Gui/src/Display/Display.cpp				\
				Gui/src/AEntity/AEntity.cpp				\
				Gui/src/Settings/Settings.cpp			\
				Gui/src/Inventory/Inventory.cpp			\
				Gui/src/TeamsDisplay/TeamsDisplay.cpp

TEST_SRC =

SERVER_OBJ = $(SERVER_SRC:%.c=obj/%.o)
GUI_OBJ = $(GUI_SRC:%.cpp=obj/%.o)

AI_NAME = zappy_ai
GUI_NAME = zappy_gui
SERVER_NAME = zappy_server

SERVER_FLAGS = -I Server/include -I Debug -lm
GUI_FLAGS = -lraylib -lpthread -lGL -I Debug 		\
        											\
			-I Gui/src/Egg 							\
			-I Gui/include 							\
			-I Gui/src/Tile			 				\
			-I Gui/src/Menu 						\
			-I Gui/src/Items 						\
			-I Gui/src/Scene						\
			-I Gui/src/Error 						\
			-I Gui/src/Player 						\
			-I Gui/src/Button 						\
			-I Gui/src/Client 						\
			-I Gui/src/Sockets 						\
			-I Gui/src/Display 						\
			-I Gui/src/AEntity 						\
			-I Gui/src/Settings						\
			-I Gui/src/Inventory 					\
			-I Gui/src/Items/Food 					\
			-I Gui/src/Items/Sibur 					\
			-I Gui/src/Items/AItem 					\
			-I Gui/src/TeamsDisplay 				\
			-I Gui/src/Items/Phiras 				\
			-I Gui/src/Items/Linemate 				\
			-I Gui/src/Items/Mendiane 				\
			-I Gui/src/Items/Thystame 				\
			-I Gui/include/interfaces				\
			-I Gui/src/Items/Deraumere				\

ALL_FLAGS = $(SERVER_FLAGS) $(GUI_FLAGS)
CFLAGS = -Werror -Wall -Wextra -Iinclude
TEST_FLAGS = --coverage -lcriterion $(CFLAGS) $(ALL_FLAGS)

PYTHONPATH = Ai/src

NC = \033[0m
RED = \033[1;31m
BLUE = \033[1;34m
GREEN = \033[1;32m

BAR_LENGTH := 40

define progress_bar
	@if [ ! -f $(2) ]; then												\
		echo 1 > $(2);													\
	fi; 																\
	count=$$(cat $(2) 2>/dev/null || echo 1); 							\
	total=$$(echo $$(($(words $(3))))); 								\
	if [ -z "$$count" ] || [ "$$count" = "" ]; then						\
		count=1;														\
	fi; 																\
	progress=$$(($$count * 100 / $$total)); 							\
	if [ $$progress -gt 100 ]; then										\
		progress=100;													\
	fi; 																\
	bar_fill=$$(($$progress * $(BAR_LENGTH) / 100)); 					\
	bar=$$(printf "%0.s=" $$(seq 1 $$bar_fill)); 						\
	space=$$(($(BAR_LENGTH) - $$bar_fill)); 							\
	if [ $$progress -lt 100 ]; then 									\
		empty=$$(printf "%0.s " $$(seq 1 $$space)); 					\
	else 																\
		empty=""; 														\
	fi; 																\
	printf "\r[\033[1;34m%s%s\033[0m] %3d%%								\
	\033[1;32m%s\033[0m\n" "$$bar" "$$empty" "$$progress" "$(1)"
endef

all: zappy_server zappy_gui zappy_ai

debug: CFLAGS += -g
debug: all

Debug/libLogger.so:
	@$(MAKE) libLogger.so -s -C Debug

Debug/libLogger.a:
	@$(MAKE) libLogger.a -s -C Debug

$(AI_NAME): Debug/libLogger.so
	@echo -e "$(GREEN)Linking $@ with shared Logger lib...$(NC)"
	@nuitka --standalone --onefile Ai/src/startAi.py --output-filename=zappy_ai

$(SERVER_NAME): $(SERVER_OBJ) Debug/libLogger.a
	@echo 1 > .server_counter
	@echo -e "$(GREEN)Linking $@ with static Logger lib...$(NC)"
	@gcc -o $@ $(SERVER_OBJ) Debug/libLogger.a $(CFLAGS) $(SERVER_FLAGS)

$(GUI_NAME): $(GUI_OBJ) Debug/libLogger.a
	@echo 1 > .gui_counter
	@echo -e "$(GREEN)Linking $@ with static Logger lib...$(NC)"
	@g++ -o $@ $(GUI_OBJ) Debug/libLogger.a $(CFLAGS) $(GUI_FLAGS)

obj/Server/%.o: Server/%.c
	@mkdir -p $(dir $@)
	@if [ ! -f .server_counter ]; then echo 1 > .server_counter; fi
	@$(call progress_bar,Compiling $<...,.server_counter,$(SERVER_OBJ))
	@gcc -c -o $@ $< $(CFLAGS) $(SERVER_FLAGS)
	@count=$$(cat .server_counter 2>/dev/null || echo 1);	\
	echo $$((count + 1)) > .server_counter

obj/Gui/%.o: Gui/%.cpp
	@mkdir -p $(dir $@)
	@if [ ! -f .gui_counter ]; then echo 1 > .gui_counter; fi
	@$(call progress_bar,Compiling $<...,.gui_counter,$(GUI_OBJ))
	@g++ -c -o $@ $< $(CFLAGS) $(GUI_FLAGS)
	@count=$$(cat .gui_counter 2>/dev/null || echo 1);		\
	echo $$((count + 1)) > .gui_counter

obj/test/%.o: %.c
	@echo -e "$(GREEN)Compiling $<...$(NC)"
	@mkdir -p $(dir $@)
	@gcc -c -o $@ $< $(SRC_NO_MAIN) $(TEST_SRC) $(TEST_FLAGS) $(CFLAGS)

obj:
	@mkdir -p obj obj/Server obj/Gui

unit_test: Debug/libLogger.so
	@echo -e "$(GREEN)Compiling unit tests...$(NC)"
	@gcc -o unit_tests $(SRC_NO_MAIN) $(TEST_SRC) $(TEST_FLAGS)

tests_run: unit_test
	@echo -e "$(GREEN)Start unit tests...$(NC)"
	@echo -e "$(GREEN)Python tests :$(NC)"
	@PYTHONPATH=.:$(PYTHONPATH) pytest --cov=Ai/src	\
	--cov-report=term-missing tests -vv
	@PYTHONPATH=.:$(PYTHONPATH) pytest --cov=Ai/src	\
	--cov-report=html tests
	@echo -e "$(GREEN)C/C++ tests :$(NC)"
	@./unit_tests

clean:
	@if [ -d obj ]; then echo -e "$(RED)Cleaning objects$(NC)"; fi
	@find . -type d -name "__pycache__" -exec rm -rf {} +
	@rm -rf .coverage htmlcov .pytest_cache
	@rm -rf obj .server_counter .gui_counter
	@rm -f *.gcda *.gcno
	@rm -rf startAi.*
	@$(MAKE) -s -C Debug clean

fclean: clean
	@if [ -e "$(SERVER_NAME)" ]; then echo -e 	\
	"$(RED)Cleaning server binary$(NC)"; fi
	@if [ -e "$(GUI_NAME)" ]; then echo -e "$(RED)Cleaning gui binary$(NC)"; fi
	@if [ -e "$(AI_NAME)" ]; then echo -e "$(RED)Cleaning ai binary$(NC)"; fi
	@rm -f $(SERVER_NAME) $(GUI_NAME) $(AI_NAME) unit_tests
	@$(MAKE) -s -C Debug fclean

re: fclean all
