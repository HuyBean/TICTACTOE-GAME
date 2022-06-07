// 21127511 - NGUYEN QUOC HUY
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstring>
#include <time.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
const int MAX = 50;
// STRUCTURES FOR TICTACTOE
struct Point
{
    int Hor;
    int Ver;
};
struct Suggestion
{
    int Row;
    int Col;
};
struct Information
{
    int timeremain = 10;
    char name[15] = "BOT";
    char icon;
    int Winning = 0;
    Suggestion Suggest;
    Point Coordinate;
};
struct tictactoe
{
    bool PVE = false;
    int size = 0;
    int wincheck = 0;
    int countdraw = 0;
    int Textcolor = 0;
    int Backgroundcolor = 0;
    int MatchesPlayed = 0;
    char board[MAX][MAX];
    Information player[2];
};

// PRINT BOARD FUNCTIONS
void Print_horizontal_coordinates(int size)
{
    cout << "  ";
    for (int i = 1; i < (1 + size); i++)
        cout << "    " << i << "      ";
    cout << "\n";
}
void Print_horizontal_line(int size)
{
    cout << "  ";
    for (int i = 0; i < size; i++)
        cout << " --------- ";
    cout << "\n";
}
void Print_vertical_line(int size)
{
    cout << "  ";
    for (int i = 0; i < size; i++)
        cout << "|         |";
    cout << "\n";
}
void Print_Board(tictactoe A)
{
    int k = 1;
    Print_horizontal_coordinates(A.size);
    for (int i = 0; i < A.size; i++)
    {
        Print_horizontal_line(A.size);
        Print_vertical_line(A.size);
        for (int j = 0; j < A.size; j++)
        {
            if (j == 0)
            {
                cout << k << " |    " << A.board[i][j] << "    |";
            }
            else
            {
                cout << "|    " << A.board[i][j] << "    |";
            }
        }
        cout << '\n';
        Print_vertical_line(A.size);
        Print_horizontal_line(A.size);
        k = k + 1;
    }
}

// RANDOM FUCTION FOR PVE
int random_PVE(int Min, int Max)
{
    return Min + rand() % (Max + 1 - Min);
}

// SUGGEST MOVING
void SuggestionPlayer1(tictactoe &A)
{
    A.player[0].Suggest.Row = random_PVE(1, A.size);
    A.player[0].Suggest.Col = random_PVE(1, A.size);
    while (A.board[A.player[0].Suggest.Row - 1][A.player[0].Suggest.Col - 1] == A.player[0].icon || A.player[0].Suggest.Row == 0 || A.player[0].Suggest.Col == 0 || A.board[A.player[0].Suggest.Row - 1][A.player[0].Suggest.Col - 1] == A.player[1].icon || A.player[0].Suggest.Row > A.size || A.player[0].Suggest.Col > A.size)
    {
        A.player[0].Suggest.Row = random_PVE(1, A.size);
        A.player[0].Suggest.Col = random_PVE(1, A.size);
    }
    cout << "!!Hints for " << A.player[0].name << ": You can choose the coordinate (" << A.player[0].Suggest.Row << ", " << A.player[0].Suggest.Col << ").\n";
}
void SuggestionPlayer2(tictactoe &A)
{
    A.player[1].Suggest.Row = random_PVE(1, A.size);
    A.player[1].Suggest.Col = random_PVE(1, A.size);
    while (A.board[A.player[1].Suggest.Row - 1][A.player[1].Suggest.Col - 1] == A.player[1].icon || A.player[1].Suggest.Row == 0 || A.player[1].Suggest.Col == 0 || A.board[A.player[1].Suggest.Row - 1][A.player[1].Suggest.Col - 1] == A.player[0].icon || A.player[1].Suggest.Row > A.size || A.player[1].Suggest.Col > A.size)
    {
        A.player[1].Suggest.Row = random_PVE(1, A.size);
        A.player[1].Suggest.Col = random_PVE(1, A.size);
    }
    cout << "!!Hints for " << A.player[1].name << ": You can choose the coordinate (" << A.player[1].Suggest.Row << ", " << A.player[1].Suggest.Col << ").\n";
}

// INPUT FUNCTIONS
void Init_Playername(tictactoe &A)
{
    cout << " Now please enter player 1 name ";
    cin.getline(A.player[0].name, 15);
    cout << " Now please enter player 2 name ";
    cin.getline(A.player[1].name, 15);
}
void Init_PVE_Playername(tictactoe &A)
{
    cout << " Now please enter player 1 name ";
    cin.getline(A.player[0].name, 15);
    char name[15] = "BOT";
    // A.player[1].name = "BOT";
    cout << "\n Your opponient's name is : " << A.player[1].name << endl;
}
void Init_Restricted_Time(tictactoe &A)
{
    cout << " Input restricted time for each player : ";
    cin >> A.player[0].timeremain;
    A.player[1].timeremain = A.player[0].timeremain;
}
void Init_Board(tictactoe &A)
{
    for (int i = 0; i < A.size * A.size; i++)
    {
        for (int j = 0; j < A.size * A.size; j++)
        {
            A.board[i][j] = ' ';
        }
    }
}
void Input_XPlayer_Turn(tictactoe &A)
{
    cout << A.player[0].name << " turn \n";
    cout << A.player[0].name << " has " << A.player[0].timeremain << " time left \n";
    cout << " Input the Row coordinate ( number ) = ";
    cin >> A.player[0].Coordinate.Hor;
    cout << " Input the Col coordinate ( number ) = ";
    cin >> A.player[0].Coordinate.Ver;
    while (A.board[A.player[0].Coordinate.Hor - 1][A.player[0].Coordinate.Ver - 1] == A.player[0].icon || A.player[0].Coordinate.Hor == 0 || A.player[0].Coordinate.Ver == 0 || A.board[A.player[0].Coordinate.Hor - 1][A.player[0].Coordinate.Ver - 1] == A.player[1].icon || A.player[0].Coordinate.Hor > A.size || A.player[0].Coordinate.Ver > A.size)
    {
        cout << " This box has been blocked . Please enter another coordinate \n ";
        cout << " Input the Row coordinate ( number ) = ";
        cin >> A.player[0].Coordinate.Hor;
        cout << " Input the Col coordinate ( number ) = ";
        cin >> A.player[0].Coordinate.Ver;
    }
    A.board[A.player[0].Coordinate.Hor - 1][A.player[0].Coordinate.Ver - 1] = A.player[0].icon;
    A.player[0].timeremain--;
}
void Input_Environment_Player_Turn(tictactoe &A)
{
    A.player[1].Coordinate.Hor = random_PVE(1, A.size);
    A.player[1].Coordinate.Ver = random_PVE(1, A.size);
    while (A.board[A.player[1].Coordinate.Hor - 1][A.player[1].Coordinate.Ver - 1] == A.player[0].icon || A.player[1].Coordinate.Hor == 0 || A.player[1].Coordinate.Ver == 0 || A.board[A.player[1].Coordinate.Hor - 1][A.player[1].Coordinate.Ver - 1] == A.player[1].icon || A.player[1].Coordinate.Hor > A.size || A.player[1].Coordinate.Ver > A.size)
    {
        A.player[1].Coordinate.Hor = random_PVE(1, A.size);
        A.player[1].Coordinate.Ver = random_PVE(1, A.size);
    }
    A.board[A.player[1].Coordinate.Hor - 1][A.player[1].Coordinate.Ver - 1] = A.player[1].icon;
    A.player[1].timeremain--;
}
void Input_OPlayer_Turn(tictactoe &A)
{
    cout << A.player[1].name << " turn \n";
    cout << A.player[1].name << " has " << A.player[1].timeremain << " time left \n";
    //  SuggestionPlayer2(A);
    cout << " Input the Row coordinate ( number ) = ";
    cin >> A.player[1].Coordinate.Hor;
    cout << " Input the Col coordinate ( number ) = ";
    cin >> A.player[1].Coordinate.Ver;
    while (A.board[A.player[1].Coordinate.Hor - 1][A.player[1].Coordinate.Ver - 1] == A.player[0].icon || A.player[1].Coordinate.Hor == 0 || A.player[1].Coordinate.Ver == 0 || A.board[A.player[1].Coordinate.Hor - 1][A.player[1].Coordinate.Ver - 1] == A.player[1].icon || A.player[1].Coordinate.Hor > A.size || A.player[1].Coordinate.Ver > A.size)
    {
        cout << " This box has been blocked . Please enter another coordinate \n";
        cout << " Input the Row coordinate ( number ) = ";
        cin >> A.player[1].Coordinate.Hor;
        cout << " Input the Col coordinate ( number ) = ";
        cin >> A.player[1].Coordinate.Ver;
    }
    A.board[A.player[1].Coordinate.Hor - 1][A.player[1].Coordinate.Ver - 1] = A.player[1].icon;
    A.player[1].timeremain--;
}
int BackgroundColor(int text, int bg)
{
    int i;
    if (text <= 15 && text >= 0 && bg <= 15 && bg >= 0)
    {
        i = (16 * bg) + text;
    }
    else
    {
        i = 1;
    }
    return i;
}
int Setting_Color(tictactoe A)
{
    cout << " Please set your favorite text and background color\n";
    for (int i = 0; i < 16; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
        cout << i << "  ";
    }
    cout << "\nAccording to above example. Input  number to choose the text color : ";
    cin >> A.Textcolor;
    cout << "According to above example. Input  number to choose the background color : ";
    cin >> A.Backgroundcolor;
    int color = BackgroundColor(A.Textcolor, A.Backgroundcolor);
    return color;
}

// CHECK WIN FUNCTIONS - ALL CASE TRUE WITH N*N BOARD
void Check_Horizontal_Winner(char board[][MAX], int size, char name0[], char name1[], char icon0, char icon1, int wincheck, int &win)
{
    for (int i = 0; i < size; i++)
    {
        int countX = 0, countO = 0;
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == icon0)
            {
                countX++;
                if (countX == wincheck)
                {
                    win = 1;
                    cout << name0 << " Won this match ";
                }
            }
            if (board[i][j] != icon0)
            {
                countX = 0;
            }
            if (board[i][j] == icon1)
            {
                countO++;
                if (countO == wincheck)
                {
                    win = 1;
                    cout << name1 << " Won this match ";
                }
            }
            if (board[i][j] != icon1)
            {
                countO = 0;
            }
        }
    }
}
void Check_Vertical_Winner(char board[][MAX], int size, char name0[], char name1[], char icon0, char icon1, int wincheck, int &win)
{
    for (int j = 0; j < size; j++)
    {
        int countX = 0, countO = 0;
        for (int i = 0; i < size; i++)
        {
            if (board[i][j] == icon0)
            {
                countX++;
                if (countX == wincheck)
                {
                    win = 1;
                    cout << name0 << " Won this match ";
                }
            }
            if (board[i][j] != icon0)
            {
                countX = 0;
            }
            if (board[i][j] == icon1)
            {
                countO++;
                if (countO == wincheck)
                {
                    win = 1;
                    cout << name1 << " Won this match ";
                }
            }
            if (board[i][j] != icon1)
            {
                countO = 0;
            }
        }
    }
}
void Check_Diagonal_Winner(char board[][MAX], int size, char name0[], char name1[], char icon0, char icon1, int wincheck, int &win)
{
    int countX = 0, countO = 0;
    for (int k = 0; k < size; k++)
    {
        if (board[k][k] == icon0)
        {
            countX++;
            if (countX == wincheck)
            {
                win = 1;
                cout << name0 << " Won this match ";
            }
        }
        if (board[k][k] != icon0)
        {
            countX = 0;
        }
        if (board[k][k] == icon1)
        {
            countO++;
            if (countO == wincheck)
            {
                win = 1;
                cout << name1 << " Won this match ";
            }
        }
        if (board[k][k] != icon1)
        {
            countO = 0;
        }
    }
}
void Check_Vice_Diagonal_Winner(char board[][MAX], int size, char name0[], char name1[], char icon0, char icon1, int wincheck, int &win)
{
    int countX = 0, countO = 0;
    for (int k = 0; k < size; k++)
    {
        if (board[k][size - 1 - k] == icon0)
        {
            countX++;
            if (countX == wincheck)
            {
                win = 1;
                cout << name0 << " Won this match ";
            }
        }
        if (board[k][size - 1 - k] != icon0)
        {
            countX = 0;
        }
        if (board[k][size - 1 - k] == icon1)
        {
            countO++;
            if (countO == wincheck)
            {
                win = 1;
                cout << name1 << " Won this match ";
            }
        }
        if (board[k][size - 1 - k] != icon1)
        {
            countO = 0;
        }
    }
}
void Check_Above_Diagonal_Winner(char board[][MAX], int size, char name0[], char name1[], char icon0, char icon1, int wincheck, int &win)
{
    for (int x = 0; x < (size - 1); x++)
    {
        int countX = 0, countO = 0;
        for (int k = 0; k < size; k++)
        {
            if (board[k][k + 1 + x] == icon0)
            {
                countX++;
                if (countX == wincheck)
                {
                    win = 1;
                    cout << icon0 << " Won this match ";
                }
            }
            if (board[k][k + 1 + x] != icon0)
            {
                countX = 0;
            }
            if (board[k][k + 1 + x] == icon1)
            {
                countO++;
                if (countO == wincheck)
                {
                    win = 1;
                    cout << name1 << " Won this match ";
                }
            }
            if (board[k][k + 1 + x] != icon1)
            {
                countO = 0;
            }
        }
    }
}
void Check_Below_Diagonal_Winner(char board[][MAX], int size, char name0[], char name1[], char icon0, char icon1, int wincheck, int &win)
{
    for (int x = 0; x < (size - 1); x++)
    {
        int countX = 0, countO = 0;
        for (int k = 0; k < size; k++)
        {
            if (board[k + 1][k + x] == icon0)
            {
                countX++;
                if (countX == wincheck)
                {
                    win = 1;
                    cout << name0 << " Won this match ";
                }
            }
            if (board[k + 1][k + x] != icon0)
            {
                countX = 0;
            }
            if (board[k + 1][k + x] == icon1)
            {
                countO++;
                if (countO == wincheck)
                {
                    win = 1;
                    cout << name1 << " Won this match ";
                }
            }
            if (board[k + 1][k + x] != icon1)
            {
                countO = 0;
            }
        }
    }
}
void Check_Above_Vice_Diagonal_Winner(char board[][MAX], int size, char name0[], char name1[], char icon0, char icon1, int wincheck, int &win)
{
    for (int x = 0; x < (size - 1); x++)
    {
        int countX = 0, countO = 0;
        for (int k = 0; k < size; k++)
        {
            if (board[k][size - k - 2 - x] == icon0)
            {
                countX++;
                if (countX == wincheck)
                {
                    win = 1;
                    cout << name0 << " Won this match ";
                }
            }
            if (board[k][size - k - 2 - x] != icon0)
            {
                countX = 0;
            }
            if (board[k][size - k - 2 - x] == icon1)
            {
                countO++;
                if (countO == wincheck)
                {
                    win = 1;
                    cout << name1 << " Won this match ";
                }
            }
            if (board[k][size - k - 2 - x] != icon1)
            {
                countO = 0;
            }
        }
    }
}
void Check_Below_Vice_Diagonal_Winner(char board[][MAX], int size, char name0[], char name1[], char icon0, char icon1, int wincheck, int &win)
{
    for (int x = 0; x < (size - 1); x++)
    {
        int countX = 0, countO = 0;
        for (int k = 0; k < size; k++)
        {
            if (board[k + 1][size - 1 - k - x] == icon0)
            {
                countX++;
                if (countX == wincheck)
                {
                    win = 1;
                    cout << name0 << " Won this match ";
                }
            }
            if (board[k + 1][size - 1 - k - x] != icon0)
            {
                countX = 0;
            }
            if (board[k + 1][size - 1 - k - x] == icon1)
            {
                countO++;
                if (countO == wincheck)
                {
                    win = 1;
                    cout << name1 << " Won this match ";
                }
            }
            if (board[k + 1][size - 1 - k - x] != icon1)
            {
                countO = 0;
            }
        }
    }
}
void Check_Winner(tictactoe &A, int &win)
{
    Check_Horizontal_Winner(A.board, A.size, A.player[0].name, A.player[1].name, A.player[0].icon, A.player[1].icon, A.wincheck, win);
    Check_Vertical_Winner(A.board, A.size, A.player[0].name, A.player[1].name, A.player[0].icon, A.player[1].icon, A.wincheck, win);
    Check_Diagonal_Winner(A.board, A.size, A.player[0].name, A.player[1].name, A.player[0].icon, A.player[1].icon, A.wincheck, win);
    Check_Vice_Diagonal_Winner(A.board, A.size, A.player[0].name, A.player[1].name, A.player[0].icon, A.player[1].icon, A.wincheck, win);
    Check_Above_Diagonal_Winner(A.board, A.size, A.player[0].name, A.player[1].name, A.player[0].icon, A.player[1].icon, A.wincheck, win);
    Check_Below_Diagonal_Winner(A.board, A.size, A.player[0].name, A.player[1].name, A.player[0].icon, A.player[1].icon, A.wincheck, win);
    Check_Above_Vice_Diagonal_Winner(A.board, A.size, A.player[0].name, A.player[1].name, A.player[0].icon, A.player[1].icon, A.wincheck, win);
    Check_Below_Vice_Diagonal_Winner(A.board, A.size, A.player[0].name, A.player[1].name, A.player[0].icon, A.player[1].icon, A.wincheck, win);
}
int Draw_Game(tictactoe A)
{
    int count = 0;
    if (A.player[0].timeremain <= 0 && A.player[1].timeremain <= 0)
    {
        return 1;
    }
    for (int i = 0; i < A.size; i++)
    {
        for (int j = 0; j < A.size; j++)
            if (A.board[i][j] == ' ')
                count++;
    }
    if (count != 0)
    {
        return 0;
    }
    return 1;
}

// RESULT FUNCTION
void PlayGame(tictactoe &A)
{
    memset(A.board, 0, 100);
    int win = 0;
    int Draw = 0;
    Init_Board(A);
    Print_Board(A);
    cout << "ARE YOU READY ? LET'S GOOOOOOO !!!\n";
    system("pause");
    while (win == 0 && Draw == 0)
    {
        SuggestionPlayer1(A);
        Input_XPlayer_Turn(A);
        system("cls");
        Print_Board(A);
        Check_Winner(A, win);
        if (win == 1)
        {
            A.player[0].Winning++;
        }
        if (win != 1)
        {
            Draw = Draw_Game(A);
        }
        if (win == 0 && Draw == 0)
        {
            if (A.PVE == false)
            {
                SuggestionPlayer2(A);
                Input_OPlayer_Turn(A);
                system("cls");
                Print_Board(A);
                Check_Winner(A, win);
                if (win == 1)
                {
                    A.player[1].Winning++;
                }
            }
            if (A.PVE == true)
            {
                Input_Environment_Player_Turn(A);
                system("cls");
                Print_Board(A);
                Check_Winner(A, win);
                if (win == 1)
                {
                    A.player[1].Winning++;
                }
            }
        }
        if (win != 1)
        {
            Draw = Draw_Game(A);
        }
        if (Draw == 1)
        {
            cout << " This match's drawed, well played.";
            A.countdraw++;
        }
    }
}
void Count_Statistic(tictactoe A)
{
    cout << "\n Number of match played : " << A.MatchesPlayed << "\n";
    cout << " Number of match player  " << A.player[0].name << " win: " << A.player[0].Winning << "\n";
    cout << " Percentage the player  " << A.player[0].name << " win:  " << (float)A.player[0].Winning / A.MatchesPlayed * 100 << "%\n";
    cout << " Number of match player  " << A.player[1].name << " win: " << A.player[1].Winning << "\n";
    cout << " Percentage the player  " << A.player[1].name << " win:  " << (float)A.player[1].Winning / A.MatchesPlayed * 100 << "%\n";
    cout << " Number of match Draw is : " << A.MatchesPlayed - A.player[0].Winning - A.player[1].Winning << "\n";
}

// TUTORIAL
void Tutorial()
{
    cout << " ================== TUTORIAL FOR THE TICTACTOE GAME  ====================== \n\n";
    cout << " + Firstly, you choose to play sound during the game or not. \n\n";
    cout << " + You can choose between playing with person (PVP) or enrivonment (PVE). \n\n";
    cout << " + Input your name and your opponent's name.\n\n";
    cout << " + Input size of tictactoe board (N*N) (up to you). \n\n";
    cout << " + Input the winning check that you want, but it must be less or equal than the size. \n\n";
    cout << " + SPECIALLY, you can input the restricted time for each player to make the game harder. \n\n";
    cout << " + Input your icon and opponient's icon to the game. \n\n";
    cout << " + Choose the text and background color for your game. Done, and you can enjoy the game. \n\n";
    cout << " + The goal of this game is to achieve highest streak in one horizontal line or vertical line or diagonal line which equal than the winning check point.\n\n";
    cout << " + Player 1 will go first. \n\n";
    cout << " + The time restricted will countdown each move.\n\n";
    cout << " + During the game there will be some hints for each player \n\n";
    cout << " + The first player get the right winning check will be the winner , do not enter the chosen coordinate. \n\n";
    cout << " + If player insert wrong coordinate, the system will ask to insert again. \n\n";
    cout << " + If the board is filled and none player win , there will be count as a draw match. \n\n";
    cout << " + The statistic will be print after each match. \n\n";
    cout << " + Finally, you can choose to play again as you want. If choose to play again, the system will save the previous statistic.\n\n";
    cout << "\n            Do you get it ? Now let's play!!!!!!!!! \n\n";
}

// GAME INTRO - SETTING - SELECTION
void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void INTRO(int &key)
{
    char board = 'w';
    while (board != ' ')
    {
        gotoxy(30, 0);
        cout << "===================== WELCOME TO ======================= ";
        gotoxy(15, 2);
        cout << R"(
          ________  ______   ______         ________   ______    ______         ________   ______   ________ 
         |        \|      \ /      \       |        \ /      \  /      \       |        \ /      \ |        \
          \$$$$$$$$ \$$$$$$|  $$$$$$\       \$$$$$$$$|  $$$$$$\|  $$$$$$\       \$$$$$$$$|  $$$$$$\| $$$$$$$$
            | $$     | $$  | $$   \$$         | $$   | $$__| $$| $$   \$$         | $$   | $$  | $$| $$__    
            | $$     | $$  | $$               | $$   | $$    $$| $$               | $$   | $$  | $$| $$  \   
            | $$     | $$  | $$   __          | $$   | $$$$$$$$| $$   __          | $$   | $$  | $$| $$$$$   
            | $$    _| $$_ | $$__/  \         | $$   | $$  | $$| $$__/  \         | $$   | $$__/ $$| $$_____ 
            | $$   |   $$ \ \$$    $$         | $$   | $$  | $$ \$$    $$         | $$    \$$    $$| $$     \
             \$$    \$$$$$$  \$$$$$$           \$$    \$$   \$$  \$$$$$$           \$$     \$$$$$$  \$$$$$$$$
                                                                                                                                                                                           
)"
             << "\n";
        gotoxy(35, 15);
        cout << "  =========================================  ";
        if (board == 'w' || board == 72)
        {
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 14);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
            }
            key = 1;
        }
        gotoxy(35, 16);
        cout << "||                                         ||";
        gotoxy(35, 17);
        cout << "||                 START                   ||";
        gotoxy(35, 18);
        cout << "||                                         ||";
        gotoxy(35, 19);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 21);
        cout << "  =========================================  ";

        if (board == 's' || board == 80)
        {
            key = 2;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 20);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
            }
        }
        gotoxy(35, 22);
        cout << "||                                         ||";
        gotoxy(35, 23);
        cout << "||                  END                    ||";
        gotoxy(35, 24);
        cout << "||                                         ||";
        gotoxy(35, 25);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";
        board = _getch();
    }
    system("cls");
}
void INTRO_NEXT(int &key)
{
    key = 1;
    char board = '0';
    while (board != ' ')
    {
        gotoxy(35, 0);
        cout << "================== MENU GAME =================\n";
        gotoxy(35, 5);
        cout << "  =========================================  ";
        if (board == 'w' || board == 72)
            key--;
        if (board == 's' || board == 80)
            key++;

        if (key == 1 || key % 3 == 1)
        {
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 6);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
            }
            // key = 1;
        }
        gotoxy(35, 6);
        cout << "||                                         ||";
        gotoxy(35, 7);
        cout << "||                TUTORIAL                 ||";
        gotoxy(35, 8);
        cout << "||                                         ||";
        gotoxy(35, 9);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 11);
        cout << "  =========================================  ";

        if (key == 2 || key % 3 == 2)
        {
            // key = 2;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 12);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
            }
        }
        gotoxy(35, 12);
        cout << "||                                         ||";
        gotoxy(35, 13);
        cout << "||                 PLAY                    ||";
        gotoxy(35, 14);
        cout << "||                                         ||";
        gotoxy(35, 15);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 17);
        cout << "  =========================================  ";
        if (key == 3 || key % 3 == 0)
        {
            // key = 3;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 16);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
            }
        }
        gotoxy(35, 18);
        cout << "||                                         ||";
        gotoxy(35, 19);
        cout << "||                 QUIT                    ||";
        gotoxy(35, 20);
        cout << "||                                         ||";
        gotoxy(35, 21);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";
        board = _getch();
    }
    system("cls");
}
void ENDING(int &key)
{
    char board = 'w';
    while (board != ' ')
    {
        gotoxy(30, 0);
        cout << "===================== WANNA PLAY AGAIN ?? =================== \n";
        gotoxy(35, 5);
        cout << "  =========================================  ";
        if (board == 'w' || board == 72)
        {
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 6);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
            }
            key = 1;
        }
        gotoxy(35, 6);
        cout << "||                                         ||";
        gotoxy(35, 7);
        cout << "||              PLAY AGAIN                 ||";
        gotoxy(35, 8);
        cout << "||                                         ||";
        gotoxy(35, 9);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 11);
        cout << "  =========================================  ";

        if (board == 's' || board == 80)
        {
            key = 0;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 12);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
            }
        }
        gotoxy(35, 12);
        cout << "||                                         ||";
        gotoxy(35, 13);
        cout << "||                QUIT GAME                ||";
        gotoxy(35, 14);
        cout << "||                                         ||";
        gotoxy(35, 15);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";
        board = _getch();
    }
    system("cls");
}
void Music()
{
    int music = -1;
    char board = 'w';
    while (board != ' ')
    {
        gotoxy(30, 0);
        cout << "===================== SETTING GAME ======================= ";
        gotoxy(30, 0);
        cout << "===================== MUSIC / AUDIO ======================= ";

        gotoxy(35, 6);
        cout << "  =========================================  ";
        if (board == 'w' || board == 72)
        {
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 5);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
            }
            music = 1;
        }
        gotoxy(35, 7);
        cout << "||                                         ||";
        gotoxy(35, 8);
        cout << "||             TURN ON MUSIC               ||";
        gotoxy(35, 9);
        cout << "||                                         ||";
        gotoxy(35, 10);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 12);
        cout << "  =========================================  ";

        if (board == 's' || board == 80)
        {
            music = 2;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 11);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
            }
        }
        gotoxy(35, 13);
        cout << "||                                         ||";
        gotoxy(35, 14);
        cout << "||            TURN OFF MUSIC               ||";
        gotoxy(35, 15);
        cout << "||                                         ||";
        gotoxy(35, 16);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";
        board = _getch();
    }
    system("cls");
    if (music == 1)
        PlaySound(TEXT("Supper_Mario.wav"), NULL, SND_LOOP | SND_ASYNC);
    else
        PlaySound(NULL, NULL, 0);
}
void PVE(bool &bot)
{
    char board = 'w';
    while (board != ' ')
    {
        gotoxy(30, 0);
        cout << "===================== SETTING GAME ======================= ";
        gotoxy(30, 0);
        cout << "===================== PVP / PVE ========================= ";

        gotoxy(35, 6);
        cout << "  =========================================  ";
        if (board == 'w' || board == 72)
        {
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 5);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
            }
            bot = false;
        }
        gotoxy(35, 7);
        cout << "||                                         ||";
        gotoxy(35, 8);
        cout << "||                  PVP                    ||";
        gotoxy(35, 9);
        cout << "||                                         ||";
        gotoxy(35, 10);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";

        gotoxy(35, 12);
        cout << "  =========================================  ";

        if (board == 's' || board == 80)
        {
            bot = true;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 11);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
            }
        }
        gotoxy(35, 13);
        cout << "||                                         ||";
        gotoxy(35, 14);
        cout << "||                  PVE                    ||";
        gotoxy(35, 15);
        cout << "||                                         ||";
        gotoxy(35, 16);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =========================================  ";
        board = _getch();
    }
    system("cls");
}
void Init_Setting(tictactoe &A)
{
    gotoxy(15, 0);
    cout << " ==================================SETTING GAME ================================= \n";
    if (A.PVE == false)
    {
        Init_Playername(A);
    }
    if (A.PVE == true)
    {
        Init_PVE_Playername(A);
    }
    cout << " Input the size of TicTacToe board : ";
    cin >> A.size;
    cout << " Input the winning checking point (must be less or equal than board's size): ";
    cin >> A.wincheck;
    Init_Restricted_Time(A);
    cout << " Please input the icon you want ( 1 character)\n";
    cout << " Input icon for player 1 : ";
    cin >> A.player[0].icon;
    if (A.PVE == false)
    {
        cout << " Input icon for player 2 : ";
        cin >> A.player[1].icon;
    }
    else
    {
        A.player[1].icon = '#';
        if (A.player[1].icon == A.player[0].icon)
            A.player[1].icon = '$';
    }
}

int main()
{
    tictactoe A;
    srand((int)time(NULL));
    int menu = 0, color = 0;
    int again = 1;
    int key = 0;
    INTRO(key);
    while (key == 1)
    {
        INTRO_NEXT(menu);
        while (menu == 1)
        {
            Tutorial();
            system("pause");
            system("cls");
            INTRO_NEXT(menu);
            system("cls");
        }
        while (again == 1)
        {
            if (menu == 2)
            {
                Music();
                PVE(A.PVE);
                Init_Setting(A);
                color = Setting_Color(A);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
                PlayGame(A);
                A.MatchesPlayed++;
                Count_Statistic(A);
                system("pause");
            }
            if (menu == 2)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                system("cls");
                ENDING(again);
            }
            if (menu == 3)
            {
                again = 2;
                break;
            }
        }
        if (key == 2)
        {
            break;
        }
    }
    return 0;
}