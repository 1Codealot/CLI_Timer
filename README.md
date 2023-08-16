# CLI_Timer ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)

This is a Rubik's cube training timer (some what similar to cstimer) used in the command line. 

# Commands

### Implemented
`2`
`3`
`4`
`5`
`6`
`7`
are commands to choose the scramble type (e.g. 3 means 3x3x3 puzzle)

`c`
continuous means that after entering a time (which currently does nothing) it'll produce a new scramble of the same type. (If `c` is not inputted it'll only do one scramble and exit after a time is inputted)

<br>

`S` <br>
skewb <br>
`M` <br>
megaminx <br>
`P` <br>
pyraminx <br>
`k` <br>
clock.
<br>
<br>

`-s{sessionName}`
This will either:
* create a new session if "session_name" does not exist.
* open a session if "session_name" does exist
It will always be continuous so `c` isn't needed
 
###### NOTE: you are able to change the scramble type of a session

#### Example commands
`CLI_Timer.exe 3` This will generate a single scramble for a 3x3 <br>
`CLI_Timer.exe 5 c` This will continually generate scrambles for a 5x5. This will NOT save to a file. <br>
`CLI_Timer.exe M -sMegaminx_Session` This will continually generate scrambles for megaminx. This will save to a file called Megaminx_Session.CLI_T_S.

### To be implemented

`q` <br>
square one (may not exist cus im dumb) 

# Other things to be implemented
* Better outputting
  * Displaying averages
