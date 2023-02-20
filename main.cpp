// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TxxL
// Names: PRAVIN A/L KUNASEGRAN | MAEVINARSH A/L LOGANATHAN | MALINY A/P THANARAJ
// IDs: 1221303877 |  1211103476 | 1211100910
// Emails: 1221303877@student.mmu.edu.my | 1211103476@student.mmu.edu.my| 1211100910@student.mmu.edu.my
// Phones: 0125547295 | 0107872493 | 0166113563
// *********************************************************

#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <conio.h>

using namespace std;


//to only accept alphabetical letters & spaces as input.
bool lettersOrSpaces(const std::string& str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        // make sure each character is A-Z or a space
        if (!std::isalpha(str[i]) && !std::isspace(str[i]))
        {
            return false; ///< at least one "no match"
        }
    }
    return true;  ///< all characters meet criteria
}

//gameboard
class AlienZombieGameBoard
{
private:
    vector< vector<char> > gameboardsize_; // convention to put trailing underscore
    int board_rows_, board_columns_, zombie_count_; // to indicate private data

public:
    AlienZombieGameBoard(int board_rows, int board_columns, int zombie_count)
    {
        init(board_rows, board_columns, zombie_count);
    }

    void init(int board_rows, int board_columns, int zombie_count)
    {
        zombie_count_ = zombie_count;
        board_rows_ = board_rows;
        board_columns_ = board_columns;

        char objects[] = { 'h','p','r','<','>','^','v','W',' ',' ' };
        int noOfObjects = 10; // number of objects in the objects array

        static random_device device;
        uniform_int_distribution<int> random(0, noOfObjects - 1);

        // create dynamic 2D array using vector
        gameboardsize_.resize(board_columns_); // create empty rows
        for (int i = 0; i < board_columns_; ++i)
        {
            gameboardsize_[i].resize(board_rows_); // resize each row
        }

        // put random characters into the vector array
        for (int i = 0; i < board_columns_; ++i)
        {
            for (int j = 0; j < board_rows_; ++j)
            {
                //int objNo = rand() % noOfObjects;
                int objNo = random(device);
                gameboardsize_[i][j] = objects[objNo];
            }
        }
    }

    vector< vector<char>> getGameBoard() {
        return gameboardsize_;
    }

    void modGameBoard(vector<char> c, int rows, int columns) {

    }

    void display() const
    {
        // comment this out during testing
        // system("cls"); // OR system("clear"); for Linux / MacOS

        cout << setw(15); //diff group
        cout << "        .: Alien vs Zombie :.        " << endl;

        // for each row
        for (int i = 0; i < board_columns_; ++i)
        {
            // display upper border of the row
            cout << "  ";
            for (int j = 0; j < board_rows_; ++j)
            {
                cout << "+-";
            }
            cout << "+" << endl;

            // display row number
            //cout << setw(2) << (board_columns_ - i);
            cout << setw(2) << i + 1;

            // display cell content and border of each column
            for (int j = 0; j < board_rows_; ++j)
            {
                cout << "|" << gameboardsize_[i][j];
            }
            cout << "|" << endl;
        }

        // display lower border of the last row
        cout << "  ";
        for (int j = 0; j < board_rows_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        // display column number
        cout << "  ";
        for (int j = 0; j < board_rows_; ++j)
        {
            int digit = (j + 1) / 10;
            cout << " ";
            if (digit == 0)
                cout << " ";
            else
                cout << digit;
        }
        cout << endl;
        cout << "  ";
        for (int j = 0; j < board_rows_; ++j)
        {
            cout << " " << (j + 1) % 10;
        }
        cout << endl << endl;
    }

    void repopulate() {

        char objects[] = { 'h','p','r','<','>','^','v','W',' ',' ' };
        int noOfObjects = 10; // number of objects in the objects array

        static random_device device;
        uniform_int_distribution<int> random(0, noOfObjects - 1);

        for (int i = 0; i < board_columns_; ++i)
        {
            for (int j = 0; j < board_rows_; ++j)
            {
                //int objNo = rand() % noOfObjects;
                if (gameboardsize_[i][j] == '.') { // Clean trails
                    int objNo = random(device);
                    gameboardsize_[i][j] = objects[objNo];
                }
            }
        }

    }

    int getColumn() const {
        return board_columns_;
    }

    int getRow() const {
        return board_rows_;
    }

    void setZombieCount(int& z) {
        zombie_count_ = z;
    }

    int getZombieCount() {
        return zombie_count_;
    }

    void setObject(int& x, int& y, char& ch) {
        gameboardsize_[y][x] = ch;
    }

    void modObject(int& x, int& y, char& ch) {

        gameboardsize_[y][x] = ch;

    }

    char getObject(int x, int y) const {

        return gameboardsize_[y][x];
    }

    void clearBoard() {

        gameboardsize_.clear();

    }

    void resizeBoard(int& c ,int& r , int& z) {

        init(r,c,z);

    }

    bool isEmpty(int x, int y) {
        return isspace(gameboardsize_[y][x]);
    }

    bool isInsideMap(int x, int y) {
        return !isspace(gameboardsize_[y][x]);
    }

    bool isHalt(int x, int y) {

        if (isdigit(gameboardsize_[y][x])) {
            return true;
        }
        if (gameboardsize_[y][x] == 'r') {

            return true;
        }

        return false;
    }

    bool isDigit(int x, int y) {

        if (isdigit(gameboardsize_[y][x])) {
            return true;

        }
    };
};

// //
//Zombie, the enemies of the game.
class Zombie {
private:
    int life_, attack_, range_, x_, y_, max_x, max_y;
public:
    Zombie() {

    }
    Zombie(int x, int y) {

        life_ = ((rand() % 5) + 1) * 50;
        attack_ = ((rand() % 5) + 1) * 5;
        range_ = (rand() % 3) + 1;
        x_ = rand() % x;
        y_ = rand() % y;

    }

    Zombie(int x, int y, int h, int a, int R) {

        life_ = h;
        attack_ = a;
        range_ = R;
        x_ = x;
        y_ = y;

    }

    void modLife(int x) {
        life_ = life_ - x;
    }

    void initPos(AlienZombieGameBoard& playingBoard, int z) {

        char ch = (char)(48 + z + 1);

        while (playingBoard.isDigit(x_, y_) || playingBoard.getObject(x_,y_) == 'A') {
            char X = playingBoard.getObject(x_, y_);
            y_ = rand() % playingBoard.getRow();
            x_ = rand() % playingBoard.getColumn();
        }


        playingBoard.setObject(x_, y_, ch);
    }

    void move(AlienZombieGameBoard& playingBoard, int i) {


        int c = playingBoard.getColumn();
        int r = playingBoard.getRow();

            int new_x = x_;
            int new_y = y_;

            int RAND = rand() % 4;
            if (RAND == 0) {
                if (x_ < c) {
                    new_x++;
                }
                else {
                    new_x--;
                }
            }
            if (RAND == 1) {
                if (x_ > 0) {
                    new_x--;
                }
                else {
                    new_x++;
                }
            }
            if (RAND == 2) {
                if (y_ > 0) {
                    new_y--;
                }
                else {
                    new_y++;
                }
            }
            if (RAND == 3) {
                if (y_ < r) {
                    new_y--;
                }
                else {
                    new_y++;
                }
            }

            if (isdigit(playingBoard.getObject(new_x,new_y))) {

                cout << " " << endl;
                cout << "Zombie " << (i + 1) << " couldn't move as there is another zombie blocking it's path." << endl;
                cout << " " << endl;
                _getch();
                return;

            }
            if (playingBoard.getObject(new_x, new_y) == 'A') {

                cout << " " << endl;
                cout << "Zombie " << (i+1) << " attacked alien as it was blocking it's path." << endl;
                cout << " " << endl;
                _getch();
                attack(x_, y_, i);
                return;
            }

            i++;
            string id = to_string(i);

            char trail = '.';

            playingBoard.setObject(x_, y_, trail);
            playingBoard.setObject(new_x, new_y, id[0]);
            x_ = new_x;
            y_ = new_y;
    }

    bool attack(int x, int y, int i ) {

        int diff_x = abs(x - x_);
        int diff_y = abs(y - y_);

        if (diff_x + diff_y < range_) {
            cout << " " << endl;
            cout << "Zombie " << (i+1) << " attacked alien for " << attack_ << " damage. Press any key to continue..." << endl;
            cout << " " << endl;
            _getch();

            return true;
        }

        cout << " " << endl;
        cout << "Zombie " << (i+1) << " is out of range to attack alien." << endl;
        cout << " " << endl;
        _getch();
        return false;
    }

    int getX() {
        return x_;
    }

    int getY() {
        return y_;
    }
    int getLife() {
        if (life_ < 0)
        {
            life_ = 0;
        }
        return life_;
    }
    int getAttack() {
        return attack_;
    }
    int getRange() {
        return range_;
    }


    //TODO : getY(), getX(), move(), and else
};

//Alien (The Hero of this game)
class Alien {

private:
    int life_{ 100 }, attack_{ 0 }, x_, y_;
    char heading_{ 'A' };

public:
    Alien() {};

    int getX() const {
        return x_;
    }

    int getY() const {
        return y_;
    }

    void setX(int& x) {

        x_ = x;

    }

    void setY(int& y) {
        y_ = y;
    }

    int getLife() {
    //int getLife() const {
        //return life_;
        if (life_ > 100)
        {
            life_ = 100;
        }
        return life_;
    }

    void setLife(int& L) {
        life_ = L;
    }

    void modLife(int x) {
        life_ = life_ - x;
    }

    int getAttack() const {
        return attack_;
    }

    void alienStatus() {
        cout << "Alien: Life: " << life_ << "Attack: " << attack_;
    }

    void turnContext(Alien& player, std::vector<Zombie>& Z) {

        cout << "" << endl;
        cout << "Alien    : Life = " << player.getLife() << " | Attack = " << player.getAttack() << endl;
        for (int i = 0; i < Z.size(); i++) {
            cout << "Zombie " << (i + 1) << " : Life = " << Z[i].getLife() << " | Attack = " << Z[i].getAttack() << " | Range : " << Z[i].getRange() << endl;
        }
        cout << "" << endl;
    }

    void initPos(AlienZombieGameBoard& playingBoard) {

        x_ = playingBoard.getRow()/2;
        y_ = (playingBoard.getColumn() / 2);

        playingBoard.setObject(x_, y_, heading_);
    }

    void move(const string& input, AlienZombieGameBoard& playingBoard, std::vector<Zombie>& Z) {
        char trail = '.';
        char pickup = ' ';
        bool halt = false; //As long as halt is false, the Alien will keep on moving. Halt becomes true when zombie/rock/wall is hit.
        string dir = input;

        while (!halt) {

            system("cls");

            int old_x = x_;
            int old_y = y_;

            if (dir == "left") {


                if (old_x > 0) {
                    old_x--;
                    pickup = playingBoard.getObject(old_x, old_y);
                }
                else {
                    halt = true; //Hit Left Wall
                }
            }
            if (dir == "right") {

                if (old_x < playingBoard.getRow() - 1) {
                    old_x++;
                    pickup = playingBoard.getObject(old_x, old_y);
                }
                else {
                    halt = true;  //Hit Right Wall
                }
            }
            if (dir == "up") {

                if (old_y > 0) {
                    old_y--;
                    if (old_y != 0) {
                        pickup = playingBoard.getObject(old_x, old_y);
                    }
                }
                else {
                    halt = true;
                }
            }
            if (dir == "down") {

                if (old_y < playingBoard.getColumn() - 1) {
                    old_y++;
                    pickup = playingBoard.getObject(old_x, old_y);
                }
                else {
                    halt = true;
                }
            }

            playingBoard.display();

            cout << "" << endl;
            if (!halt) {

                cout << "Alien moved one step " << dir << "." << endl;

                if (pickup == '>') {
                    attack_ = attack_ + 20;
                    cout << "Alien changed direction to right and gained 20 damage." << " [Attack = " << attack_ << "]" << endl;
                    dir = "right";
                }
                if (pickup == '<') {
                    dir = "left";
                    attack_ = attack_ + 20;
                    cout << "Alien changed direction to left and gained 20 damage." << " [Attack = " << attack_ << "]" << endl;
                }
                if (pickup == '^') {
                    dir = "up";
                    attack_ = attack_ + 20;
                    cout << "Alien changed direction to up and gained 20 damage." << " [Attack = " << attack_ << "]" << endl;

                }
                if (pickup == 'v') {
                    dir = "down";
                    attack_ = attack_ + 20;
                    cout << "Alien changed direction to down and gained 20 damage." << " [Attack = " << attack_ << "]" << endl;

                }
                if (pickup == 'h') {

                    cout << "Alien found health pickup." << endl;
                    life_ = life_ + 20;
                }
                if (pickup == 'p') {

                    for (int i = 0; i < Z.size(); i++) {

                        Z.at(i).modLife(20);
                        cout << "Alien found pod that damaged Zombie " << (i + 1) << " for 20 damage." << endl;
                    }

                }
                if (pickup == 'r') {

                    cout << "Alien hit a rock and has stopped moving." << endl;
                    halt = true;

                    int RAND = rand() % 3;

                    if (RAND == 0) {
                        char c = 'h';
                        playingBoard.setObject(old_x, old_y, c);
                        cout << "The rock broke and revealed a healthpack." << endl;
                    }
                    if (RAND == 1) {
                        char c = 'p';
                        playingBoard.setObject(old_x, old_y, c);
                        cout << "The rock broke and revealed a pod." << endl;
                    }
                    if (RAND == 2) {
                        char c = ' ';
                        playingBoard.setObject(old_x, old_y, c);
                        cout << "The rock broke and revealed nothing." << endl;
                    }

                }
                if (pickup == 'W') {

                    cout << "Alien hit a wall and has stopped moving." << endl;
                    halt = true;
                }
                if (isdigit(pickup)) {


                    int atkx = int(pickup - '1');

                    if (Z[atkx].getLife() > 0) {

                        cout << "Alien damaged Zombie " << pickup << " for " << getAttack() << " damage." << endl;

                        Z[atkx].modLife(attack_);

                        if (Z[atkx].getLife() > 0) {
                            cout << "Alien stopped due to zombie blocking route." << endl;
                            life_ = life_ - Z[atkx].getAttack();
                            cout << "Zombie attacked Alien for " << Z[atkx].getAttack() << " damage." << endl;
                            halt = true;
                        }

                        else {
                            cout << "Alien defeated Zombie " << pickup << endl;
                        }
                    }

                }
            }
            else {
                cout << "Alien has hit an obstacle and stopped moving." << endl;
            }
            cout << "Press any key to continue..." << endl;
            cout << "" << endl;
            _getch();

            if (!halt) {
                playingBoard.setObject(x_, y_, trail);
                playingBoard.setObject(old_x, old_y, heading_);
                x_ = old_x;
                y_ = old_y;
            }
            else {
                attack_ = 0;
            }

        }

    }
};




void showGameSettings(const int& board_rows, const int& board_columns, const int& zombie_count)//, const string &change_game_settings)
{


    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    : " << board_rows << endl;
    cout << "Board Columns : " << board_columns << endl;
    cout << "Zombie Count  : " << zombie_count << endl;
    cout << " " << endl;

}


void displayMenu();
void username(string& username);
void showGameSettings(const int& board_rows, const int& board_columns, const int& zombie_count);
void startGame(const int& board_columns, const int& board_rows, const int& zombie_count);
void gameControl(Alien& player, AlienZombieGameBoard& playingBoard, std::vector<Zombie>& Z);
void gameDashboard();

void commandHelp(AlienZombieGameBoard& playingBoard) {

    playingBoard.display();
    cout << "" << endl;
    cout << "Help Section" << endl;
    cout << "1. Up, Down, Left, Right : Move the alien according to the typed direction" << endl;
    cout << "2. Arrow                 : Changes the direction of an arrow on the map." << endl;
    cout << "3. Save                  : Saves current progress for later." << endl;
    cout << "4. Load                  : Loads progress saved." << endl;
    cout << "5. Quit                  : Exits the Program." << endl;
    cout << "" << endl;
};

void changeGameSettings(int& board_rows, int& board_columns, int& zombie_count);


int main()
{
    cin.clear();
    int board_rows;
    int board_columns;
    int zombie_count;
    //string change_game_settings;
    int change_game_settings_numerical;
    string username;

    board_rows = 5;
    board_columns = 9;
    zombie_count = 1;

    Alien player;


    username;
    showGameSettings(board_rows, board_columns, zombie_count);
    changeGameSettings(board_rows, board_columns, zombie_count);

}


//To change game settings, gets input from user if its a 'y' or 'n', and converts y or n to integer and then goes through if and else. y = change game settings, n = game starts like normal

/*string username(string$ username)
{
    cout << "Please enter your username: ";
    cin >> username;
}*/

void changeGameSettings(int& board_rows, int& board_columns, int& zombie_count)

{
    string change_game_settings;
    cout << "Do you wish to change the game settings (y/n)? => ";

    while (getline(cin, change_game_settings) && !lettersOrSpaces(change_game_settings)) //Accepts only alphabets and spaces. Numbers and special characters cannot.
        // NUMBERS & SPECIAL CHARS REJECTED
    {

        cout << "   " << endl;
        cout << "no numbers or special characters!" << endl;
        cout << "   " << endl;
        cout << "Do you wish to change the game settings (y/n)? => ";
        cin >> change_game_settings;

    }



    {
        change_game_settings.erase(std::remove_if(change_game_settings.begin(), change_game_settings.end(), ::isspace), //to remove spaces for the "change_game_settings" variable
            change_game_settings.end());

    }


    while (change_game_settings != "y" && change_game_settings != "n") //if "change_game_settings" doesn't equal to y AND n
    {
        //ONLY ACCEPTS Y or N
        cout << " " << endl;
        cout << "Only enter y/n!" << endl;
        cout << "                                                                       " << endl;
        cout << "Do you wish to change the game settings (y/n)? => ";
        cin >> change_game_settings;
    }

    //cout << change_game_settings; //temporary for testing

    const char* y = "y";
    const char* n = "n";

    int change_game_settings_numerical;

    //cout << change_game_settings_numerical; //temporary for testing

    if (change_game_settings == y)
    {
        change_game_settings_numerical = 1;
    }
    else
    {
        change_game_settings_numerical = 2;
    }

    //cout << change_game_settings_numerical; //temporary for testing

    if (change_game_settings_numerical == 2)
    {
        startGame(board_columns, board_rows, zombie_count);

    }
    if (change_game_settings_numerical == 1)
    {
        cout << " " << endl;
        cout << "Board Settings" << endl;
        cout << "----------------" << endl;
        cout << "Enter rows => "; //must be numbers only. no alphabets, no special characters, no spaces.
        while (true)
        {
            cin >> board_rows;

            if (!cin) //to disallow alphabets and special characters
            {
                cout << "- Alphabets and Special Characters are not allowed! Try again." << endl;
                cin.clear();                                                  //clears existing input value which has the alphabets or special characters.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');          //copy this line if you dont want the program to accept alphabets and special characters.
                cout << "Enter rows => ";                                     //repeat the warning message
                continue;                                                     //must put to avoid the program to stop working
            }


            if (board_rows % 2 == 0) //if the user enters an even number
            {
                cout << "Please enter an odd number!" << endl;
                cin.clear();
                cout << "Enter rows => ";
                continue;
            }

            if (board_rows < 1) //to disallow negative values and 0. There is no such thing as month 0,-1,-2,-3,-4,...
            {
                cout << "Cannot enter 0 or numbers below that" << endl;
                cin.clear();
                cout << "Enter rows => ";
                continue;
            }
            else break;
            //else break;
             // else is to break the loop



        }

        cout << "Enter columns => "; //must be numbers only. no alphabets, no special characters, no spaces.
        while (true)
        {

            cin >> board_columns;

            if (!cin)
            {
                cout << "- Alphabets and Special Characters are not allowed! Try again." << endl;
                cin.clear();                                                  //clears existing input value which has the alphabets or special characters.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');          //copy this line if you dont want the program to accept alphabets and special characters.
                cout << "Enter columns => ";                                     //repeat the warning message
                continue;                                                     //must put to avoid the program to stop working
            }

            if (board_columns % 2 == 0) //if the user enters an even number
            {
                cout << "Please enter an odd number!" << endl;
                cin.clear();
                cout << "Enter columns =>";
                continue;

            }

            if (board_columns < 1) //to disallow negative values and 0. There is no such thing as month 0,-1,-2,-3,-4,...
            {
                cout << "Cannot enter 0 or numbers below that" << endl;
                cin.clear();
                cout << "Enter columns => ";
                continue;
            }
            else break;
            //else break;


            /*if (board_columns = board_columns % 2 == 0) //if the user enters an even number
            {
                cout << "Please enter an odd number!" << endl;
                cin.clear();
                cout << "Enter columns =>" ;
                continue;

            }*/


        }

        cout << " " << endl;
        cout << "Zombie Settings" << endl;
        cout << "----------------" << endl;
        cout << "Enter number of zombies => ";
        while (true)
        {
            cin >> zombie_count;

            if (!cin) //to disallow alphabets and special characters
            {
                cout << "- Alphabets and Special Characters are not allowed! Try again." << endl;
                cin.clear();                                                  //clears existing input value which has the alphabets or special characters.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');          //copy this line if you dont want the program to accept alphabets and special characters.
                cout << "Enter number of zombies => ";                                     //repeat the warning message
                continue;                                                     //must put to avoid the program to stop working
            }

            //cout << zombie_count; temporary

            if (zombie_count >= 10 || zombie_count <= 0) //the assignment limits zombie count to 9
            {
                cout << "Number of zombies should be between 1 to 9 only!" << endl;
                cin.clear();
                cout << "Enter number of zombies => ";
                continue;
            }

            else break; // else is to break the loop

        }

        cout << "Settings Updated." << endl;
        startGame(board_columns, board_rows, zombie_count);
    }


}

//starts game

void startGame(const int& board_columns, const int& board_rows, const int& zombie_count) {

    vector<Zombie> Z;

    AlienZombieGameBoard playingBoard = AlienZombieGameBoard(board_columns, board_rows, zombie_count);

    Alien player;
    player.initPos(playingBoard);
    srand(time(0));
    for (int i = 0; i < zombie_count; i++) {
        Zombie* A = new Zombie(board_columns, board_rows);
        A->initPos(playingBoard, i);
        Z.push_back(*A);
        delete(A);
    }

    playingBoard.display();

    while (true) {


        //gameDashboard()
        gameControl(player, playingBoard, Z);
    }

}

void arrowEdit(AlienZombieGameBoard& playingBoard) {

    int x, y;
    string dir;

    cout << "" << endl;
    cout << "Enter row of arrow :";

    while (true)
    {
        cin >> y;

        if (!cin) //to disallow alphabets and special characters
        {
            cout << "- Alphabets and Special Characters are not allowed! Try again." << endl;
            cin.clear();                                                  //clears existing input value which has the alphabets or special characters.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');          //copy this line if you dont want the program to accept alphabets and special characters.
            cout << "Enter row of arrow :";                                     //repeat the warning message
            continue;                                                     //must put to avoid the program to stop working
        }

        if (y < 1 || y > playingBoard.getColumn()) //to disallow negative values and 0. There is no such thing as month 0,-1,-2,-3,-4,...
        {
            cout << "Cannot enter values out of bounds." << endl;
            cin.clear();
            cout << "Enter row of arrow :";
            continue;
        }
        else break; // else is to break the loop

    }

    cout << "" << endl;

    cout << "Enter column of arrow :";
    while (true)
    {
        cin >> x;

        if (!cin) //to disallow alphabets and special characters
        {
            cout << "- Alphabets and Special Characters are not allowed! Try again." << endl;
            cin.clear();                                                  //clears existing input value which has the alphabets or special characters.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');          //copy this line if you dont want the program to accept alphabets and special characters.
            cout << "Enter column of arrow :";                                     //repeat the warning message
            continue;                                                     //must put to avoid the program to stop working
        }

        if (x < 1 || x > playingBoard.getRow()) //to disallow negative values and 0. There is no such thing as month 0,-1,-2,-3,-4,...
        {
            cout << "Cannot enter values out of bounds." << endl;
            cin.clear();
            cout << "Enter column of arrow :";
            continue;
        }
        else break; // else is to break the loop

    }

    x--; y--;

    char arrow = playingBoard.getObject(x, y);

    if (arrow == '<' || arrow == '>' || arrow == '^' || arrow == 'v') {
        cout << "" << endl;
        cout << "Set direction of arrow (up, down, left, right): ";

        while (true)
        {
            cin >> dir;
            cout << "" << endl;
            cout << dir << endl;
            cout << "" << endl;

            if (dir == "up" || dir == "down" || dir == "left" || dir == "right")
            {
                break;
                //must put to avoid the program to stop working
            }
            else {

                cout << "Invalid Direction." << endl;
                cout << "" << endl;
                cin.clear();                 //clears existing input value which has the alphabets or special characters.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Set direction of arrow (up, down, left, right):";                                     //repeat the warning message
                continue;

            }

        }

        cout << "" << endl;
        cout << "Direction of (R, C) : " << y << ", " << x << " set as " << dir << endl;
        cout << "" << endl;
        cout << "Press any key to see changes...";

        if (dir == "up") {
            char n = '^';
            playingBoard.modObject(x, y, n);
        }
        if (dir == "down") {
            char n = 'v';
            playingBoard.modObject(x, y, n);
        }
        if (dir == "left") {
            char n = '<';
            playingBoard.modObject(x, y, n);
        }
        if (dir == "right") {
            char n = '>';
            playingBoard.modObject(x, y, n);
        }

        _getch();

    }
    else {
        cout << "" << endl;
        cout << "Arrow does not exist at this location." << endl;
        cout << "" << endl;
        cout << "Press any key to continue...";
        _getch();

    }
}

//I havent finish game control and objects yet. WIP:

//vector<int>& vect

void ZombieMove(Alien& player, std::vector<Zombie> Z) {



}

string leaderboard()
{

}
void gameControl(Alien& player, AlienZombieGameBoard& playingBoard, std::vector<Zombie>& Z) {

    string userInput;
    system("cls");

    bool victory = false;
    bool defeat  = false;
    int nextAction;
    int totalScore = 0;

    for (int i = 0; i < Z.size(); i++) {

        if (Z[i].getLife() < 1) {
            victory = true;
        }
        if (player.getLife() < 1) {
            defeat = true;
        }
        /*else {
            victory = false;
            break;}*/
    }
playingBoard.display();
player.turnContext(player, Z);

if (victory) {
    totalScore = ((totalScore + 10)*(player.getLife()));
    cout << endl;
    cout << "All Zombies are defeated. Congratulations!" << endl;
    cout << endl;
    cout << "Enter 1 to Play Again" << endl;
    cout << "Enter 2 to View Total Score of the Game" << endl;
    cout << "Enter 3 to Quit" << endl;
    cout << "Please Enter: ";
    cin >> nextAction;


if (nextAction == 1) {
     main(); // Function to reset the game
}

else if (nextAction == 2) {
    cout << "Your total score is " << totalScore << endl;
    cout << "Enter anything to continue" << endl;

}

else if (nextAction == 3) {
    std::abort(); // to quickly exit the game
    //cout << "Press any key to EXIT..." << endl;
    //_getch();
}



}

    if (defeat) {

        cout << "" << endl;
        cout << "Alien is defeated. Better luck next time!" << endl;
        cout << "" << endl;
        cout << "Enter 1 to Play Again" << endl;
        cout << "Enter 2 to View Total Score of the Game" << endl;
        cout << "Enter 3 to Quit" << endl;
        cout << "Please Enter: ";
        cin >> nextAction;

    if (nextAction == 1)
    {
        main();
    }

    else if (nextAction == 2)
    {
        cout << "Your total score is " << totalScore << endl;
        cout << "Enter anything to continue" << endl;
    }

    else if(nextAction == 3)
    {
            std::abort; //to quickly exit the game
            //cout << "Press any key to EXIT..." << endl;
            //_getch();
    }

    }

//TESTING i hope i didnt screw anything here
    cout << "Command > ";
    if ((!victory && !defeat) || nextAction == 2) {
        cin >> userInput;
    }
    else {
        userInput = "quit";
    }

    if (userInput == "arrow")
        {
        arrowEdit(playingBoard);
        }

    if (userInput == "help") {
        system("cls");

        commandHelp(playingBoard);
        cout << "Press any key to continue..." << endl;
        cout << "";
        _getch();

    }if (userInput == "save") {

        std::string saveFile;
        cout << "Savefile name : ";
        cin >> saveFile;
        fstream file;
        file.open(saveFile, ios_base::out);
        vector<vector<char>> GameBoard = playingBoard.getGameBoard();

        file << playingBoard.getColumn() << endl;
        file << playingBoard.getRow() << endl;
        file << playingBoard.getZombieCount() << endl;

        file << player.getX() << endl;
        file << player.getY() << endl;
        file << player.getLife() << endl;

        for (int i = 0; i < playingBoard.getColumn(); i++) {

            for (int j = 0; j < playingBoard.getRow(); j++) {

                file << GameBoard[i][j] << endl;

            }

        }

        for (int i = 0; i < Z.size();i++) {

            file << Z[i].getLife() << endl;
            file << Z[i].getAttack() << endl;
            file << Z[i].getRange() << endl;
            file << Z[i].getX() << endl;
            file << Z[i].getY() << endl;

        }

        file.close();

    }if (userInput == "load") {

        fstream file;
        std::string loadFile;
        cout << "Savefile name : ";
        cin >> loadFile;

        file.open(loadFile);

        int c, r, z;
        string Temp;

        getline(file,Temp);
        c = atoi(Temp.c_str());
        cout << "Columns : " << c << endl;
        getline(file,Temp);
        r = atoi(Temp.c_str());
        cout << "Rows : " << r << endl;
        getline(file,Temp);
        z = atoi(Temp.c_str());
        cout << "Zombie Count : " << z << endl;

        int ph, px, py;
        getline(file, Temp);
        px = atoi(Temp.c_str());
        cout << "Alien X : " << px << endl;
        getline(file, Temp);
        py = atoi(Temp.c_str());
        cout << "Alien Y : " << py << endl;
        getline(file, Temp);
        ph = atoi(Temp.c_str());
        cout << "Alien Health : " << ph << endl;
        _getch();

        player.setLife(ph);
        player.setX(px);
        player.setY(py);

        playingBoard.setZombieCount(z);

        playingBoard.init(r,c,z);

        for (int i = 0; i < playingBoard.getColumn(); i++) {

            for (int j = 0; j < playingBoard.getRow(); j++) {
                getline(file, Temp);
                char c = Temp[0];
                playingBoard.setObject(j, i, c);
            }

        }

        Z.clear();

        for (int i = 0; i < playingBoard.getZombieCount(); i++) {

            getline(file, Temp);
            int h = atoi(Temp.c_str());
            getline(file, Temp);
            int a  = atoi(Temp.c_str());
            getline(file, Temp);
            int R  = atoi(Temp.c_str());
            getline(file, Temp);
            int x_ = atoi(Temp.c_str());
            getline(file, Temp);
            int y_ = atoi(Temp.c_str());
            Zombie* A = new Zombie(x_,y_,h,a,R);
            Z.push_back(*A);
            delete(A);

        }

        playingBoard.display();
        player.turnContext(player , Z);
        file.close();
        _getch();


    }if (userInput == "quit") {
        system("cls");

        cout << "" << endl;
        cout << "Press any key to exit..." << endl;
        cout << "" << endl;
        _getch();

        exit(EXIT_SUCCESS);
    }
    if (userInput == "up" || userInput == "down" || userInput == "left" || userInput == "right") {
        player.move(userInput, playingBoard, Z);

        for (int i = 0; i < Z.size(); i++) {

            if (Z[i].getAttack() > 0) {
                if (Z[i].attack(player.getX(), player.getY(), i)) {
                    player.modLife(Z[i].getAttack());
                }

                Z[i].move(playingBoard, i);
            }
        }

        playingBoard.repopulate();
    }


}

