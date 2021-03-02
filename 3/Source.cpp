#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
#include <thread>
#include <fstream>
using namespace std;
using namespace std::chrono_literals;

struct Position
{
    int row;
    int col;
};

enum condition {
    winner1,
    winner2,
    continue_play,
    standoff
};

void print_game_state_to_console(char** Arr)
{

    std::cout << "==a===b===c==" << '\n';
    std::cout << "= " << Arr[0][0] << " | " << Arr[0][1] << " | " << Arr[0][2] << " =1" << '\n';
    std::cout << "= " << Arr[1][0] << " | " << Arr[1][1] << " | " << Arr[1][2] << " =2" << '\n';
    std::cout << "= " << Arr[2][0] << " | " << Arr[2][1] << " | " << Arr[2][2] << " =3" << '\n';
    std::cout << "=============" << '\n';
}

void print_game_state_to_file(char** Arr)
{
    ofstream im_fayl;
    string path_html = "index.html";
    im_fayl.open(path_html);
   if (!im_fayl.is_open())
    {
        cout << "mi ban sxal e" << endl;
    }
    else
    {
        im_fayl << "<head>" << "<meta http - equiv = " << '"' << "refresh" << '"' << "content = " << '"' << '1' << '"' << "/>";
        im_fayl << " <link rel= " << '"' << "stylesheet" << '"' << " type = " << '"' << "text/css" << '"' << "href = " << '"' << "mystyle.css" << '"' << '>' << "</<head>";
        im_fayl << "<body>" << "<table> <tr><td>  " << Arr[0][0] << "</td>" << "<td>  " << Arr[0][1] << "</td> " << "<td>  " << Arr[0][2] << "</td>" << '\n' << "</tr>";
        im_fayl << "<tr><td>  " << Arr[1][0] << "</td>" << "<td>  " << Arr[1][1] << "</td> " << "<td>  " << Arr[1][2] << "</td>" << '\n' << "</tr>";
        im_fayl << "<tr><td>  " << Arr[2][0] << "</td>" << "<td>  " << Arr[2][1] << "</td> " << "<td>  " << Arr[2][2] << "</td>" << '\n' << "</tr></table>" << "</body>";

        im_fayl.close();
    }
}

void print_game_state(char** Arr)
{
    print_game_state_to_console(Arr);
    print_game_state_to_file(Arr);
}

void fillArray(char** const Arr, int  const row, int const col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            Arr[i][j] = ' ';
        }
    }
}

bool is_board_full(char** Arr)
{
    if (Arr[0][0] == ' ' || Arr[0][1] == ' ' || Arr[0][2] == ' ' ||
        Arr[1][0] == ' ' || Arr[1][1] == ' ' || Arr[1][2] == ' ' ||
        Arr[2][0] == ' ' || Arr[2][1] == ' ' || Arr[2][2] == ' ')
    {
        return false;
    }
    return true;
}

condition check_if_win(char** Arr) // stugum a 2-ic ov e haxtel
{
    /*
     * XXX
     * ---
     * ---
     */
    if (Arr[0][0] == 'O' && Arr[0][1] == 'O' && Arr[0][2] == 'O') { return winner2; }
    else if (Arr[0][0] == 'X' && Arr[0][1] == 'X' && Arr[0][2] == 'X') { return winner1; }
    /*
     * ---
     * XXX
     * ---
     */
    else if (Arr[1][0] == 'O' && Arr[1][1] == 'O' && Arr[1][2] == 'O') { return winner2; }
    else if (Arr[1][0] == 'X' && Arr[1][1] == 'X' && Arr[1][2] == 'X') { return winner1; }
    /*
     * ---
     * ---
     * XXX
     */
    else if (Arr[2][0] == 'O' && Arr[2][1] == 'O' && Arr[2][2] == 'O') { return winner2; }
    else if (Arr[2][0] == 'X' && Arr[2][1] == 'X' && Arr[2][2] == 'X') { return winner1; }
    /*
     * X--
     * X--
     * X--
     */
    else if (Arr[0][0] == 'O' && Arr[1][0] == 'O' && Arr[2][0] == 'O') { return winner2; }
    else if (Arr[0][0] == 'X' && Arr[1][0] == 'X' && Arr[2][0] == 'X') { return winner1; }
    /*
     * -X-
     * -X-
     * -X-
     */
    else if (Arr[0][1] == 'O' && Arr[1][1] == 'O' && Arr[2][1] == 'O') { return winner2; }
    else if (Arr[0][1] == 'X' && Arr[1][1] == 'X' && Arr[2][1] == 'X') { return winner1; }
    /*
     * --X
     * --X
     * --X
     */
    else if (Arr[0][2] == 'O' && Arr[1][2] == 'O' && Arr[2][2] == 'O') { return winner2; }
    else if (Arr[0][2] == 'X' && Arr[1][2] == 'X' && Arr[2][2] == 'X') { return winner1; }
    /*
     * X--
     * -X-
     * --X
     */
    else if (Arr[0][0] == 'O' && Arr[1][1] == 'O' && Arr[2][2] == 'O') { return winner2; }
    else if (Arr[0][0] == 'X' && Arr[1][1] == 'X' && Arr[2][2] == 'X') { return winner1; }
    /*
     * --X
     * -X-
     * X--
     */
    else if (Arr[0][2] == 'O' && Arr[1][1] == 'O' && Arr[2][0] == 'O') { return winner2; }
    else if (Arr[0][2] == 'X' && Arr[1][1] == 'X' && Arr[2][0] == 'X') { return winner1; }
    else if (is_board_full(Arr)) {
        return standoff;
    }
    return continue_play;
}

int get_row(const string& position)
{
    if (position.size() != 2) {
        return -1;
    }
    // row must be either 1, 2 or 3
    if (position[0] == '1' || position[0] == '2' || position[0] == '3') {
        return position[0] - '1';
    }
    if (position[1] == '1' || position[1] == '2' || position[1] == '3') {
        return position[1] - '1';
    }
    return -1;
}

int get_column(const string& position)
{
    if (position.size() != 2) {
        return -1;
    }
    // row must be either 1, 2 or 3
    if (position[0] == 'a' || position[0] == 'b' || position[0] == 'c') {
        return position[0] - 'a';
    }
    if (position[1] == 'a' || position[1] == 'b' || position[1] == 'c') {
        return position[1] - 'a';
    }
    return -1;
}

bool is_valid_position(const string& position, char** Arr)
{
    const auto row = get_row(position);
    if (row < 0 || row>2)
    {
        return false;
       
    }
    const auto column = get_column(position);
    if (column < 0 || column>2)
    {
        return false;
       
    }
    return Arr[row][column] == ' ';
}

bool make_winning_move(char** Arr, Position* empty_positions, int num_empty_position)
{
    for (int i = 0; i < num_empty_position; ++i)                       //for empty cell)
    {
        Position pos = empty_positions[i];
        Arr[pos.row][pos.col] = 'O';                  //1. put 'O' in that cell
        if (check_if_win(Arr) == winner2)
        {
            return true;
        }
        else { Arr[pos.row][pos.col] = ' '; }        //if no, remove 'O'
    }
    return false;
}

bool make_defending_move(char** Arr, Position* empty_positions, int num_empty_position)
{
    for (int i = 0; i < num_empty_position; ++i)           //for empty cell)
    {
        Position pos = empty_positions[i];
        Arr[pos.row][pos.col] = 'X';              
        if (check_if_win(Arr) == winner1)
        { //if X is winning should put O in order to defend
            Arr[pos.row][pos.col] = 'O';
            return true;
        }
        else
        {
            Arr[pos.row][pos.col] = ' ';
        }
    }
    return false;           //if we rich here, no  there were no winning move
}

void random_move(char** Arr)
{
    while (true)
    {
        int random_row = rand() % 3;
        int random_col = rand() % 3;
        if (Arr[random_row][random_col] == ' ')
        {
            Arr[random_row][random_col] = 'O';
            return;
        }
    }
}

void make_move(char** Arr)
{
    Position* empty_positions = new Position[9];
    int num_empty_position = 0;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (Arr[r][c] == ' ') {
                empty_positions[num_empty_position] = Position{ r, c };
                ++num_empty_position;
            }
        }
    }
    // we have quantity of 'num_empty_position' empty cells in which we shoul put 'O' 
    bool has_winning_move = make_winning_move(Arr, empty_positions, num_empty_position);
    if (has_winning_move) {
        return;
    }
    bool has_defending_move = make_defending_move(Arr, empty_positions, num_empty_position);
    if (has_defending_move) {
        return;
    }
    random_move(Arr);
}

void write_winner_to_file(const string& name1, condition result)
{
    ofstream im_fayl;
    string path = "index.html";
    im_fayl.open(path, ofstream::app);
    switch (result)
    {
    case winner1:
        im_fayl << " You win " << name1 << endl;  break;
    case winner2:
        im_fayl << name1 << " You lose" << endl; break;
    case standoff:
        im_fayl << "Standoff" << endl; break;
    }
    im_fayl.close();
}

void write_winner_to_console(const string& name1, condition result)
{
    switch (result) {
    case winner1:
        cout << "You Win " << name1 << endl;
        break;
        //return  system("my.exe");
    case winner2:
        cout << name1 << " You Lose " << endl;
        break;
        //return  system("my.exe");
    case standoff:
        cout << "Standoff" << endl;
        break;
        //return  system("my.exe");
    }
}

void write_winner(const string& name1, condition result)
{
    write_winner_to_file(name1, result);
    write_winner_to_console(name1, result);
}

void play()
{
    cout << "Enter your name" << endl;
    string name1;
    cin >> name1;
    const int row = 3;
    const int col = 3;
    char** Arr = new char* [row];
    for (int i = 0; i < row; ++i)
    {
        Arr[i] = new char[col];
    }
    fillArray(Arr, row, col);

    char queue = 'X';
    string const sxal = "Wrong enterance... ";
    while (true)
    {
        system("cls");
        print_game_state(Arr);
        auto result = check_if_win(Arr);
        if (result != continue_play) {
           write_winner(name1, result);
            return;
        }

        if (queue == 'X')
        {
            string position; 
            //= read_position_from_file();
            cin >> position;
           if (!is_valid_position(position, Arr)) {
                cout << sxal << endl;
                std::this_thread::sleep_for(1s);                 
               // if invalid or already occupied position, do nothing
                continue;
            }
            Arr[get_row(position)][get_column(position)] = 'X'; //queue;
        }
        else
        {
            make_move(Arr);
            std::this_thread::sleep_for(0.5s);
        }
        // change the turn
        queue = (queue == 'X') ? 'O' : 'X';
		//color
        /* if (queue == 'X')
         {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);

         }
         else { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); }*/

    }

}


int main()
{
    srand(time(NULL));
    while (true) {
        play();
    }
    return 0;
}

