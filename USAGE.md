# Commands

### NxN cube types
`2`
`3`
`4`
`5`
`6`
`7`

### Side event cube types

`S` <br>
skewb <br>
`M` <br>
megaminx <br>
`P` <br>
pyraminx <br>
`C` <br>
clock. <br>
`Q` <br>
square-1

<hr>

#### Event modifiers
`-b` (or `-B`) will generate scrambles for blindfolded events for 3x3, 4x4 and 5x5.<br>
`-MBLD{count}` will generate 3BLD scrambles for {count puzzles} at once. <br>


<hr>

`-f` will generate fmc scrambles. This will only work for 3x3

<hr>

`c`
continuous means that after entering a time (which currently does nothing) it'll produce a new scramble of the same type. (If `c` is not inputted it'll only do one scramble and exit after a time is inputted)

<hr>

`-s{sessionName}`
This will either:
* create a new session if "session_name" does not exist.
* open a session if "session_name" does exist
It will always be continuous so `c` isn't needed
<br>
On windows, the session files will save to %appdata%\CLI_Timer_Sessions.<br>
On Linux it saves to /home/your_username/.config/CLI_Timer_Sessions<br>
On MacOs it saves to /Users/your_username/Library/Application Support/CLI_Timer_Sessions<br>


<hr>

`--no_prompt`
This will not prompt you to enter in your time.
If you do `CLI_Timer 2 -sSession --no_prompt` it will say "You can't save without prompting therefore it will prompt". I'm sure you can figure out why from the message.

<hr>

`--count{number}`
This will generate {number} amount of scrambles and then quit.<br>
Example: `CLI_Timer 7 --count5 -s7x7_average`
<br>
<sub> Note: `c` argument is impiled. </sub>
<hr>

`--no_avg`
This will hide showing your current session average.<br>
`--no_prompt` impilies this.
 
<hr>

`--no_enter` will instantly output n scrambles (with the argument `--count{n}`). You MUST have `--no_prompt` and `--count`.

<hr>

`--no_format` removes the formatting (e.g. scramble taking up 1/3rd of the terminal and showing averages).

<hr>

`--cache_size{number}` will set the cache size to {number}. This means it will store {number} scrambles in the cache. The default is 50.

<hr>

`--seed{s}` allows you to set a custom seed. Any non numbers (including "-") will have their ASCII numeric value converted into a string.

<hr>

### Other commands 

`help`
This outputs a help message.

`--version` 
Outputs the current version.
<hr>

### Example commands
`CLI_Timer.exe 3` This will generate a single scramble for a 3x3 <br>
`CLI_Timer.exe 5 c` This will continually generate scrambles for a 5x5. This will NOT save to a file. <br>
`CLI_Timer.exe M -sMegaminx_Session` This will continually generate scrambles for megaminx. This will save to a file called Megaminx_Session.CLI_T_S.

<sub>NOTE: The commands do not need to be in any order.</sub>

# Entering in times
You can enter in times in the format of HH:MM:SS.DD (the `.` and `:`s are optional)<br>
For example `123456` is the same as `(00:)12:34.56`