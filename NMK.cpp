#include <iostream>
#define MAX_SIZE 40

using namespace std;

struct commands {
    const char generate[16] = { "GEN_ALL_POS_MOV" };
    const char generateGameOver[33] = { "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER" };
    const char solveGameState[17] = { "SOLVE_GAME_STATE" };
};

int LastIndex(char* str) {
    int last_id = 0;
    while (str[last_id++] != '\0');
    return --last_id;
}

bool StrCompare(char str[MAX_SIZE], const char command[]) {
    int lastIndex = LastIndex(str);

    if (command[lastIndex] != '\0')
        return false;

    for (int i = 0; i < lastIndex; i++) {
        if (str[i] != command[i])
            return false;
    }

    return true;
}

void PrintBoard(char** board, int x, int y) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isVictory(char** board, int x, int y, char player, int k, int streak, int direction, int n, int m) {
    if (board[y][x] != player)
        return false;
    if (streak == k)
        return true;

    if (direction == 0 && x < m - 1)
        return isVictory(board, x + 1, y, player, k, streak + 1, direction, n, m);
    else if (direction == 1 && x < m - 1 && y < n - 1)
        return isVictory(board, x + 1, y + 1, player, k, streak + 1, direction, n, m);
    else if (direction == 2 && y < n - 1)
        return isVictory(board, x, y + 1, player, k, streak + 1, direction, n, m);
    else if (direction == 3 && y < n - 1 && x > 0)
        return isVictory(board, x - 1, y + 1, player, k, streak + 1, direction, n, m);
    return false;
}

int winCondition(char** board, int x, int y, char player, int k) {
    int possibleMoves = 0;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (board[i][j] == '0')
                possibleMoves++;
            if (isVictory(board, j, i, player, k, 1, 0, y, x) || isVictory(board, j, i, player, k, 1, 1, y, x) ||
                isVictory(board, j, i, player, k, 1, 2, y, x) || isVictory(board, j, i, player, k, 1, 3, y, x))
                return 1;
        }
    }
    if (possibleMoves == 0)
        return -1;
    return 0;
}

int minimax(char** board, int sizeX, int sizeY, int k, char player, int highestScore, int lowestScore) {
    char opponent = '1';
    if (player == '1')
        opponent = '2';

    int result = winCondition(board, sizeX, sizeY, opponent, k);
    if (result == 1 && opponent == '1')
        return 1;
    if (result == 1 && opponent == '2')
        return -1;
    if (result == -1)
        return 0;

    if (player == '1') {
        int bestScore = -1;
        for (int y = 0; y < sizeY; y++) {
            for (int x = 0; x < sizeX; x++) {
                if (board[y][x] == '0') {
                    board[y][x] = player;
                    int score = minimax(board, sizeX, sizeY, k, opponent, highestScore, lowestScore);
                    board[y][x] = '0';
                    if (score > bestScore)
                        bestScore = score;
                    if (lowestScore < bestScore)
                        lowestScore = bestScore;
                    if (highestScore <= lowestScore)
                        return bestScore;
                }
            }
        }
        return bestScore;
    }
    else {
        int bestScore = 1;
        for (int y = 0; y < sizeY; y++) {
            for (int x = 0; x < sizeX; x++) {
                if (board[y][x] == '0') {
                    board[y][x] = player;
                    int score = minimax(board, sizeX, sizeY, k, opponent, highestScore, lowestScore);
                    board[y][x] = '0';
                    if (score < bestScore)
                        bestScore = score;
                    if (highestScore > bestScore)
                        highestScore = bestScore;
                    if (highestScore <= lowestScore)
                        return bestScore;
                }
            }
        }
        return bestScore;
    }
}

int main() {
    commands Command;
    char command[MAX_SIZE], activePlayer;
    int sizeY, sizeX, k, oneFields = 0, twoFields = 0;

    while (cin >> command) {
        cin >> sizeY >> sizeX >> k >> activePlayer;
        int possibleMoves = 0;
        char** board = new char* [sizeY];
        for (int i = 0; i < sizeY; i++)
            board[i] = new char[sizeX];

        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                cin >> board[i][j];
                if (board[i][j] == '0')
                    possibleMoves++;
                if (board[i][j] == '1')
                    oneFields++;
                if (board[i][j] == '2')
                    twoFields++;
            }
        }
        char opponentPlayer = '1';
        if (activePlayer == '1')
            opponentPlayer = '2';

        if (StrCompare(command, Command.generate)) {
            if (winCondition(board, sizeX, sizeY, opponentPlayer, k))
                possibleMoves = 0;

            cout << possibleMoves << endl;
            if (possibleMoves == 0)
                continue;
            for (int i = 0; i < sizeY; i++) {
                for (int j = 0; j < sizeX; j++) {
                    if (board[i][j] == '0') {
                        board[i][j] = activePlayer;
                        PrintBoard(board, sizeX, sizeY);
                        board[i][j] = '0';
                    }
                }
            }

        }
        if (StrCompare(command, Command.generateGameOver)) {
            if (winCondition(board, sizeX, sizeY, opponentPlayer, k))
                possibleMoves = 0;

            if (possibleMoves == 0) {
                cout << possibleMoves << endl;
                continue;
            }
            char*** boards = new char** [possibleMoves];
            bool gameOver = false;
            for (int l = 0; l < possibleMoves; l++) {
                int foundZeros = 0;
                boards[l] = new char* [sizeY];
                for (int i = 0; i < sizeY; i++) {
                    boards[l][i] = new char[sizeX];
                    for (int j = 0; j < sizeX; j++) {
                        boards[l][i][j] = board[i][j];
                        if (board[i][j] == '0') {
                            if (foundZeros == l)
                                boards[l][i][j] = activePlayer;
                            foundZeros++;
                        }
                    }
                }
                if (winCondition(boards[l], sizeX, sizeY, activePlayer, k)) {
                    cout << 1 << endl;
                    PrintBoard(boards[l], sizeX, sizeY);
                    gameOver = true;
                    break;
                }
            }
            if (gameOver)
                continue;
            cout << possibleMoves << endl;
            for (int k = 0; k < possibleMoves; k++)
                PrintBoard(boards[k], sizeX, sizeY);
        }
        else if (StrCompare(command, Command.solveGameState)) {
            int result = minimax(board, sizeX, sizeY, k, activePlayer, 1, -1);

            if (result == 1)
                cout << "FIRST_PLAYER_WINS" << endl;
            if (result == -1)
                cout << "SECOND_PLAYER_WINS" << endl;
            if (result == 0)
                cout << "BOTH_PLAYERS_TIE" << endl;
        }

        for (int i = 0; i < sizeY; i++)
            delete[] board[i];
        delete[] board;
    }

    return 0;
}