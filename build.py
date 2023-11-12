#!/bin/python3

############################### DEPRICATED; I FELL TO THE DARK SIDE :(######################################################

"""
I hate makefiles, build scripts are better.
I also don't like PEP 8.
"""

import os, sys

compiler = "g++"                        # Use argument `-c{/path/to/compiler}` to specify compiler
main_path = "./src/main.cpp"            # Use argument `-i{/path/to/mainfile}` to specify the main.cpp file to use
output_path = "./Final_Build/CLI_Timer" # Use argument `-o{/path/to/output_file_name}` to specify where you want it to compile to.
extras = []
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
            elif prefix == "-x": # For extra commands like -Wall. Usage: `./build.py -x-Wall -x-O3"` or `./build.py -x"-Wall -O3"
                extras.append(arg[2:])
            else:
                print(f"Did not understand argument: {arg} (maybe try lowercase or put the path immediately after {prefix})\nExiting.")
                sys.exit(1)

    command_to_run = compile_command_template.format(compiler, main_path, output_path)

    # Hooray! Hacky solution!!!

    for e in extras:
        command_to_run += " " + e

    confirm = input(f"Running command: {command_to_run}\nIs this OK? \nI will also delete an older version (if it exists) by running `os.remove({output_path})`\n[Y/n]\n")

    if len(confirm) == 0 or confirm.lower()[0] == "y":
        try:
            os.remove(output_path)
        except FileNotFoundError:
            print("Nothing to remove...")
        else:
            print("Something went wrong while deleting...")
            exit(1)

        os.system(command=command_to_run)
    else:
        sys.exit(0)