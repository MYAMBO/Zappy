##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## zappy_ai
##

import sys
import argparse

def parsing_ai(args):
    parser = argparse.ArgumentParser(description="", add_help=False)

    parser.add_argument("-p", dest="port", required=True, help="Port number")
    parser.add_argument("-n", dest="team_name", required=True, help="Team name")
    parser.add_argument("-h", dest="machine", default="localhost", help="Machine adress")
    parser.add_argument("-help", action="help", help="Display zappy_ai help")

    try:
        parsed_args = parser.parse_args(args[1:])
        return int(parsed_args.port), parsed_args.team_name, parsed_args.machine
    except Exception as ex:
        print("Error:", ex)
        sys.exit(84)
