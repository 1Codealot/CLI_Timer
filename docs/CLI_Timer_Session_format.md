# Introduction

This is the secification for the `*.CLI_T_S` file (new) binary format.
<br>
This is for version 1 of the file type.

# Description

## Metadata
Magic bytes: `CLI_TIMER{version_num}` (`43 4c 49 5f 54 49 4d 45 52 01`)

## Main body
In the original format it went `{scramble}§{time}~{Comment}`. <br> 
If there were penalties (i.e. +2 or DNF) it would do `{time}+` or `DNF({time})`.
<br>

In this new version, it will instead be `[02]{scramble}[03]{penalty_num}{time}[02]{comment}[03]`.

This is where `[02]` and `[03]` are the ASCII codes for "start of text" and "end of text" respectively. <br>
The `{scramble}` and `{comment}` sections are just raw strings with no compression (for version 1; hopefully not for future versions). <br>
`{penalty_num}` will be: <br>
* 1: No penalty
* 2: +2
* 3: DNF

Finally the `{time}` will be a binary representation for a float for the amount of seconds. For example, the time `1:23.45` would be stored as `42 a6 e6 66`