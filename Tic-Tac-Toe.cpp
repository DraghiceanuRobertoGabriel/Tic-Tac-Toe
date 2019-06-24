#include <iostream>
#include <string>
#include <map>
#include <bits/stdc++.h>

#define EMPTY_CELL '.'
#define FIRST_PLAYER 'X'
#define SECOND_PLAYER '0'
#define DRAW -1

using namespace std;

string board[3];
pair<int, int> player_pos;

map<string, char> who_wins;
map<string, string> best_move;

char current_player;
char other_player[128];

void startGame()
{

    current_player = 'X';

    for (int i = 0; i < 3; ++i)
    {

        board[i].resize(3, EMPTY_CELL);

    }

    player_pos.first = player_pos.second = 0;

}

void Menu()
{

    cout << "Tic, Tac, Toe";
    cout << endl;
    cout << "VS my AI";
    cout << endl;
    cout << endl;

    cout << "How to play?";
    cout << endl;
    cout << "You will be the X";
    cout << endl;
    cout << "P-PLACE THE X";
    cout << endl;
    cout << "You will use your WASD keys to move";
    cout << endl;
    cout << "W - UP";
    cout << endl;
    cout << "A - LEFT";
    cout << endl;
    cout << "S - DOWN";
    cout << endl;
    cout << "D - RIGHT";
    cout << endl;
    cout << endl;

}

int isGameRunning()
{
    for (int i = 0; i < 3; ++i) {

        if (board[i][0] != EMPTY_CELL
             && board[i][0] == board[i][1]
              && board[i][0] == board[i][2])

            return board[i][0];

        if (board[0][i] != EMPTY_CELL
             && board[0][i] == board[1][i]
              && board[0][i] == board[2][i])

            return board[0][i];

    }

    if (board[0][0] != EMPTY_CELL
         && board[0][0] == board[1][1]
          && board[0][0] == board[2][2])

        return board[0][0];

    if (board[2][0] != EMPTY_CELL
         && board[2][0] == board[1][1]
          && board[2][0] == board[0][2])

        return board[2][0];

    int has_empty_cell = -1;

    for (int i = 0; i < 3; ++i)

        for (int j = 0; j < 3; ++j)

            if (board[i][j] == EMPTY_CELL)

                has_empty_cell = 0;

    return has_empty_cell;

}

void printBoard()
{

	system("cls");

    Menu();

    for (int i = 0; i < 3; ++i) {

        for (int j = 0; j < 3; ++j)

            if (make_pair(i, j) == player_pos && isGameRunning() == 0)

                cout << current_player;

            else

                cout << board[i][j];

        cout << "\n";

    }

    cout << endl;

}


bool isInside(pair<int, int> pos)
{

    return 0 <= pos.first && pos.first < 3 && 0 <= pos.second && pos.second < 3;

}

char getCurrentPlayer(string linear_board)
{
    int num_x = 0, num_0 = 0;

    for ( c : linear_board)

        if (c == FIRST_PLAYER)

            ++num_x;

        else if (c == SECOND_PLAYER)

            ++num_0;

    if (num_x > num_0)

        return SECOND_PLAYER;

    else return FIRST_PLAYER;

}

void linearBoardToBoard(string linearBoard)
{
    for (int i = 0; i < 3; ++i)

        for (int j = 0; j < 3; ++j)

            board[i][j] = linearBoard[i * 3 + j];

}

string boardToLinearBoard()
{

    string linearBoard;

    for (int i = 0; i < 3; ++i)

        for (int j = 0; j < 3; ++j)

            linearBoard += board[i][j];

    return linearBoard;

}

int precomputeWhoWins(string linear_board)
{

    if (who_wins.find(linear_board) != who_wins.end())

        return who_wins[linear_board];

    linearBoardToBoard(linear_board);

    char state = isGameRunning();

    if (state != 0)
    {

        who_wins[linear_board] = state;

        return state;

    }

    char current_player = getCurrentPlayer(linear_board);

    char best_result = other_player[current_player];

    string best_current_move;

    for (int i = 0; i < 9; ++i)

        if (linear_board[i] == EMPTY_CELL) {

            linear_board[i] = current_player;

            char next_win = precomputeWhoWins(linear_board);

            if (next_win == current_player)
            {

                best_result = current_player;
                best_current_move = linear_board;

            }

            else if (next_win == DRAW && best_result == other_player[current_player]) {

                best_result = DRAW;
                best_current_move = linear_board;

            }

            linear_board[i] = EMPTY_CELL;

        }

    best_move[linear_board] = best_current_move;
    who_wins[linear_board] = best_result;

    return best_result;

}

int main()
{

    other_player[FIRST_PLAYER] = SECOND_PLAYER;
    other_player[SECOND_PLAYER] = FIRST_PLAYER;

    precomputeWhoWins(".........");

    startGame();
    printBoard();

    int dline[] = {1, 0, -1, 0};
    int dcol[] = {0, 1, 0, -1};

    string commands = "wasd";

    int dir_idx[250];

    dir_idx['w'] = 2;
    dir_idx['a'] = 3;
    dir_idx['s'] = 0;
    dir_idx['d'] = 1;

    while (isGameRunning() == 0)
    {

        char command;

        cin >> command;

        if (commands.find(command) != string::npos)
        {

            pair<int, int> next_pos = player_pos;
            next_pos.first += dline[dir_idx[command]];
            next_pos.second += dcol[dir_idx[command]];

            if (isInside(next_pos))

                player_pos = next_pos;

        } else if (command == 'p')
        	{

            	if (board[player_pos.first][player_pos.second] == EMPTY_CELL)
            	{

                	board[player_pos.first][player_pos.second] = current_player;

            	}

            		if (isGameRunning())

                		break;

            	string linearBoard = boardToLinearBoard();
            	linearBoardToBoard(best_move[linearBoard]);

        	}

        printBoard();

    }

    char state = isGameRunning();

    if (state == -1)

        cout << "Draw\n";

    else

        cout << state << " has won!\n";

    return 0;
}
