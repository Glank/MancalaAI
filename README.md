# MancalaAI
A simple AI for the board game Mancala

## Build Instructions
Run `make mancala` to build.

To run all the tests, run `make test`

## Usage
To run the AI, just run the binary `./mancala`
The commands below can be used to interact with the AI. Most are self explanitory.

~~~
  quit
  q
  help
  h
  aimove (1-12) (v|verbose)
  ai (1-12) (v|verbose)
    Runs a single AI move at the given level (defaults to 4 if unspecified.
    If verbose is specified then the full thought trace will also be printed.
  move [1-6]
  mv [1-6]
    Performs a single move. The spaces are numbered from the current players
    goal backwards, so the space closest to the current player's goal is 1 and
    the furthest is 6.
  print
  p
  undo (#)
    Undoes the specified number of moves. 1 by default.
  reset
  pack
    Prints a packaged board string that can be loaded with the 'unpack' command.
  unpack <packaged board>
    Loads a packaged board from the output of a pack command. The format is a
    list of all the cell's counts starting from the left most (player 2's gate)
    going counter clockwise followed by '-' if the game is in a terminal state,
    or 1 or 2 depending on the next player to move.
  autoprint [on|off]
    If autoprint is on the board will be printed after each command and turn
    automatically.
  autoai [1|2] [off|1-12]
    If an auto ai is set then an ai move at the specified level will be
    performed whenever the board is on player 1 or 2's turn (whichever is
    specified). This AI is reset by the 'reset' command.
~~~
