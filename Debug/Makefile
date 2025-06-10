##
## EPITECH PROJECT, 2025
## Logger Library
## File description:
## Makefile
##

LIB_STATIC      = libLogger.a
LIB_SHARED      = libLogger.so

C_SOURCES       = logger.c
CPP_SOURCES     = Logger.cpp

C_OBJS          = $(C_SOURCES:.c=.o)
CPP_OBJS        = $(CPP_SOURCES:.cpp=.o)

OBJS            = $(C_OBJS) $(CPP_OBJS)

CFLAGS          = -Wall -Wextra -Werror -std=c11 -I.
CPPFLAGS        = -Wall -Wextra -Werror -std=c++20 -I.

RED             = \033[1;31m
GREEN           = \033[1;32m
BLUE            = \033[1;34m
NC              = \033[0m

all: $(LIB_STATIC) $(LIB_SHARED)

$(LIB_SHARED): $(OBJS)
	@echo -e "$(BLUE)Creating shared library: $@$(NC)"
	@$(CC) -fPIC -shared -o $(LIB_SHARED) logger.c

$(LIB_STATIC): $(OBJS)
	@echo -e "$(BLUE)Creating static library: $@$(NC)"
	@ar rcs $@ $(OBJS)

%.o: %.c
	@gcc $(CFLAGS) -fPIC -c $< -o $@

%.o: %.cpp
	@g++ $(CPPFLAGS) -fPIC -c $< -o $@

clean:
	@echo -e "$(RED)Cleaning objects.$(NC)"
	@rm -f *.o *.gcda *.gcno

fclean: clean
	@echo -e "$(RED)Removing library.$(NC)"
	@rm -f $(LIB_STATIC) $(LIB_SHARED)

re: fclean all
