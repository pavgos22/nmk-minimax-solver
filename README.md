# NMK minimax solver

The project implements the game logic for a two-player board game, a variant of a connect-style game (similar to Tic-Tac-Toe). The program allows the simulation and analysis of potential game states and outcomes using various commands.

## Core Components

### Structures and Definitions

- **`commands`**: A structure containing predefined strings representing different game commands.
- **`MAX_SIZE`**: A constant that defines the maximum size of the command string.

### Helper Functions

- **`LastIndex(char* str)`**: Determines the last index of a null-terminated string.
- **`StrCompare(char str[MAX_SIZE], const char command[])`**: Compares a given command string with predefined commands.
- **`PrintBoard(char** board, int x, int y)`**: Prints the current state of the game board.
- **`isVictory(...)`**: Recursively checks for a victory condition for a given player on the board.
- **`winCondition(...)`**: Checks if there is a win or draw on the board and counts possible moves.
- **`minimax(...)`**: Implements the Minimax algorithm, used to determine the optimal move for a player by simulating all possible moves and outcomes.

## Main Logic

The `main()` function processes input commands and board states to manage and analyze the game. The input consists of a command followed by board dimensions, the win condition (`k`), the active player, and the board configuration.

## Command Handling

The program recognizes three primary commands:

- **`GEN_ALL_POS_MOV`**:
  - Generates and prints all possible board states for the active player’s next move.
  - If the opponent can immediately win, no moves are generated.

- **`GEN_ALL_POS_MOV_CUT_IF_GAME_OVER`**:
  - Similar to the first command but stops generating moves if a winning move for the active player is found and prints it immediately.

- **`SOLVE_GAME_STATE`**:
  - Uses the Minimax algorithm to determine the outcome of the current game state:
    - `"FIRST_PLAYER_WINS"` if player 1 is guaranteed to win.
    - `"SECOND_PLAYER_WINS"` if player 2 is guaranteed to win.
    - `"BOTH_PLAYERS_TIE"` if neither player can force a win (i.e., the game will end in a draw).

## Board Memory Management

The code dynamically allocates memory for the board and possible moves and carefully deallocates it to prevent memory leaks.
