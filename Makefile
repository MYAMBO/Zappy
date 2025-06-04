##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Makefile
##

SERVER_SRC				=	 	Server/src/main.c			\
								Server/src/init_server.c	\
								Server/src/garbage.c		\
								Server/src/start_server.c	\
								Server/src/poll_handling.c	\
								Server/src/handle_event.c	\

GUI_SRC 				=		Gui/src/main.cpp		\

TEST_SRC 				=								\

SERVER_OBJ				=		$(SERVER_SRC:%.c=obj/%.o)

GUI_OBJ 				= 		$(GUI_SRC:%.cpp=obj/%.o)

SERVER_NAME				=		zappy_server

GUI_NAME 				=  		zappy_gui

SERVER_FLAGS 			= 		-I Server/include

GUI_FLAGS 				= 		-I Gui/include

ALL_FLAGS 				= 		$(SERVER_FLAGS) $(GUI_FLAGS)

CFLAGS 					= 		-Werror -Wall -Wextra -Iinclude

TEST_FLAGS 				= 		--coverage -lcriterion $(CFLAGS) $(ALL_FLAGS)

RED             		=     	\033[1;31m
GREEN          			=     	\033[1;32m
BLUE          	  		=     	\033[1;34m
NC              		=     	\033[0m

all:	zappy_server zappy_gui zappy_ai

debug: CFLAGS += -g
debug: all

zappy_ai:

$(SERVER_NAME): $(SERVER_OBJ)
	@echo -e "$(GREEN)Linking $@...$(NC)"
	@gcc -o $@ $^ $(CFLAGS) $(SERVER_FLAGS)

$(GUI_NAME): $(GUI_OBJ)
	@echo -e "$(GREEN)Linking $@...$(NC)"
	@g++ -o $@ $^ $(CFLAGS) $(GUI_FLAGS)


obj/%.o: ./%.c
	@echo -e "$(GREEN)Compiling $<...$(NC)"
	@mkdir -p $(dir $@)
	@gcc -c -o $@ $< $(CFLAGS) $(SERVER_FLAGS)

obj/%.o: ./%.cpp
	@echo -e "$(GREEN)Compiling $<...$(NC)"
	@mkdir -p $(dir $@)
	@g++ -c -o $@ $< $(CFLAGS) $(GUI_FLAGS)

obj/test/%.o: ./%.c
	@echo -e "$(GREEN)Compiling $<...$(NC)"
	@mkdir -p $(dir $@)
	@g++ -c -o $@ $< $(SRC_NO_MAIN) $(TEST_SRC) $(TEST_FLAGS) $(CFLAGS)

obj:
	@mkdir -p obj obj/Server obj/Gui

unit_test:
	@echo -e "$(GREEN)Compiling units tests...$(NC)"
	@gcc -o unit_tests $(SRC_NO_MAIN) $(TEST_SRC) $(TEST_FLAGS)

tests_run: unit_test
	@echo -e "$(GREEN)Start units tests...$(NC)"
	@./unit_tests

clean:
	@rm -rf obj
	@rm -f *.gcda
	@rm -f *.gcno

fclean: clean
	@rm -f $(SERVER_NAME) $(GUI_NAME)
	@rm -f unit_tests

re:	fclean all
