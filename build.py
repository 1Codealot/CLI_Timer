#!/bin/python3

"""
I hate makefiles, build scripts are better.
"""

import os, sys

compiler = "g++"
main_path = "./src/main.cpp"
output_path = "./Final_Build/CLI_Timer"

compile_command_template = "{} {} -o {}"

if __name__ == '__main__':

    if len(sys.argv) > 1:
        for arg in sys.argv[1:]:
            if (prefix := arg[0:2]) == "-c":
                compiler = arg[2:]
            elif prefix == "-i":
                main_path = arg[2:]
            elif prefix == "-o":
                output_path = arg[2:]
            else:
                print(f"Did not understand argument: {arg} (maybe try lowercase or put the path immediately after {prefix})")

    command_to_run = compile_command_template.format(compiler, main_path, output_path)

    confirm = input(f"Running command: {command_to_run}\nIs this OK? [Y/n]\n")

    if len(confirm) == 0 or confirm.lower()[0] == "y":
        os.system(command=command_to_run)
    else:
        sys.exit(0)