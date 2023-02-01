// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT2L
// Names: MALINY A/P THANARAJ  | MAEVINARSH A/L LOGANATHAN | PRAVIN A/L KUNASEGRAN
// IDs: 1211100910  | 1211103476 | 122303877  
// Emails: 1211100910@student.mmu.edu.my |  1211103476@student.mmu.edu.my| 1221303877@student.mmu.edu.my
// Phones: 016-6113563 | 010-7872493 | 012-5547295
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
        if (! std::isalpha(str[i]) && ! std::isspace(str[i]))
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
        int board_rows_, board_columns_; // to indicate private data

    public:
        AlienZombieGameBoard(int board_rows, int board_columns)
        {
            init(board_rows, board_columns);
        }

    void init(int board_rows, int board_columns)
    {
        board_rows_ = board_rows;
        board_columns_ = board_columns;

        char objects[] = {'h','p','r','<','>','^','v',' ',' ',' '};
        int noOfObjects = 10; // number of objects in the objects array

        static random_device device;
        uniform_int_distribution<int> random(0, noOfObjects-1);

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
            cout << setw(2) << i + 1 ;

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


    int getColumn() const{
        return board_columns_;
    }

    int getRow() const {
        return board_rows_;
    }

    void setObject(int &x, int &y, char &ch){
        gameboardsize_[-(y - board_rows_)][x - 1] = ch;
    }

    char getObject(int x, int y) const{

        return gameboardsize_[-(y - board_rows_)][x - 1];
    }

    bool isEmpty(int x, int y){
        return isspace(gameboardsize_[-(y - board_rows_)][x - 1]);
    }

    bool isInsideMap(int x, int y){
        return !isspace(gameboardsize_[-(y - board_rows_)][x - 1]);
    }


};

// //

//Alien (The Hero of this game)
class Alien{
private:
    int life_ {100}, attack_ {0}, x_, y_;
    char heading_ {'A'};

public:
    Alien(){};

    int getX() const{
        return x_;
    }

    int getY() const{
        return y_;
    }

    void alienStatus(){
        cout << "Alien: Life: " << life_ << "Attack: " << attack_;
    }

    void initPos(AlienZombieGameBoard &playingBoard){

        x_ = playingBoard.getColumn() / 2; /////////////////////
        y_ = (playingBoard.getRow() / 2) + 1;

        playingBoard.setObject(x_, y_, heading_);
    }

    void move(const string &input,AlienZombieGameBoard &playingBoard){
        char trail = '.';
        if (input == "up"){
            while(playingBoard.isEmpty((x_ + 1), y_)){
                int oldPosX = x_;
                int oldPosY = y_;
                y_++;
                playingBoard.setObject(x_, y_, heading_);
                playingBoard.setObject(oldPosX, oldPosY, trail);
                }
        }else if (input == "down"){
            while(playingBoard.isEmpty((x_ - 1), y_)){
                int oldPosX = x_;
                int oldPosY = y_;
                y_--;

                playingBoard.setObject(x_, y_, heading_);
                playingBoard.setObject(oldPosX, oldPosY, trail);
            }
        }else if (input == "left"){
            while(playingBoard.isEmpty((x_ - 1), y_)){
                int oldPosX = x_;
                int oldPosY = y_;
                x_--;

                playingBoard.setObject(x_, y_, heading_);
                playingBoard.setObject(oldPosX, oldPosY, trail);
            }
        }else if(input == "right"){
            while(playingBoard.isEmpty((x_ + 1), y_)){
                int oldPosX = x_;
                int oldPosY = y_;

                x_++;
                playingBoard.setObject(x_, y_, heading_);
                playingBoard.setObject(oldPosX, oldPosY, trail);

            }
        }

    }
};


//Zombie, the enemies of the game.
class Zombie{
private:
    int life_, attack_, range_, x_, y_;
public:
    Zombie(){};

    //TODO : getY(), getX(), move(), and else
};


void gameControl(Alien &player, AlienZombieGameBoard &playingBoard);
// //

void showGameSettings (const int &board_rows, const int &board_columns, const int &zombie_count)//, const string &change_game_settings)
{


    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    : " << board_rows << endl;
    cout << "Board Columns : " << board_columns << endl;
    cout << "Zombie Count  : " << zombie_count << endl;
    cout << " " << endl;
}

void startGame(const int &board_columns, const int &board_rows, const int &zombie_count);

/*int changeGameSettings (int change_game_settings_numerical) ///problematic
//      int fact         (int n)
{
    string change_game_settings;
    cout << "Do you wish to change the game settings (y/n)? => ";  ///WHY DOES IT REPEAT???? NEEDS A FIX. Logical Error.

    while (getline(cin, change_game_settings) && !lettersOrSpaces(change_game_settings)) //Accepts only alphabets and spaces. Numbers and special characters cannot.

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
        cout << " " << endl;
        cout << "Only enter y/n!" << endl;
        cout << "                                                                       " << endl;
        cout << "Do you wish to change the game settings (y/n)? => ";
        cin >> change_game_settings;
    }


    // cout << change_game_settings << endl; //temporary //the change_game_settings variable's value is now y.

    const char* y = "y";
    const char* n = "n";

    if (change_game_settings == y)
    {
        change_game_settings_numerical = 1;
    }
    else
    {
        change_game_settings_numerical = 0;
    }

    int cgsntwo; //ans
    cgsntwo = change_game_settings_numerical;
    return cgsntwo;

    // cout << change_game_settings_numerical << endl; //temporary //WORKS WELL TILL HERE
    //cout << " " << endl; //actually this one considered as new page.
    //do if else statement for 1 and 0

} */


void displayMenu();
void showGameSettings(const int &board_rows, const int &board_columns, const int &zombie_count);
void startGame(const int &board_columns, const int &board_rows, const int &zombie_count);
void gameControl(Alien &player, AlienZombieGameBoard &playingBoard);
void gameDashboard();
void commandHelp();

int changeGameSettings (int &board_rows, int &board_columns, int &zombie_count);

main ()
{
    int board_rows;
    int board_columns;
    int zombie_count;
    //string change_game_settings;
    int change_game_settings_numerical;

    board_rows = 5;
    board_columns = 9;
    zombie_count = 1;



    Alien player;

    showGameSettings(board_rows, board_columns, zombie_count);

    changeGameSettings (board_rows, board_columns, zombie_count);





    ///USELESS THINGS:

    //cout << changeGameSettings(change_game_settings_numerical); // for testing


    /* if (changeGameSettings(change_game_settings_numerical) = 1); ///requires fix. Syntax Error
    {
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

            //cout << board_rows; //temporary

            if (board_rows < 1) //to disallow negative values and 0. There is no such thing as month 0,-1,-2,-3,-4,...
            {
                cout << "Cannot enter 0 or numbers below that" << endl;
                cin.clear();
                cout << "Enter rows => ";
                continue;
            }
            else break; // else is to break the loop

            if (board_rows = board_rows % 2 == 0) //if the user enters an even number
            {
                cout << "Please enter an odd number!" << endl;
                cin.clear();
                cout << "Enter rows =>" ;
                continue;
            }

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

            if (board_columns < 1) //to disallow negative values and 0. There is no such thing as month 0,-1,-2,-3,-4,...
            {
                cout << "Cannot enter 0 or numbers below that" << endl;
                cin.clear();
                cout << "Enter columns => ";
                continue;
            }
            else break; // else is to break the loop

            if (board_columns = board_columns % 2 == 0) //if the user enters an even number
            {
                cout << "Please enter an odd number!" << endl;
                cin.clear();
                cout << "Enter columns =>" ;
                continue;
            }
        }
    }


    if (change_game_settings_numerical == 1) ///SAME SYNTAX ERROR
    {
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

            if (zombie_count < 1) //to disallow negative values and 0. There is no such thing as month 0,-1,-2,-3,-4,...
            {
                cout << "Cannot enter 0 or numbers below that" << endl;
                cin.clear();
                cout << "Enter number of zombies => ";
                continue;
            }
            else break; // else is to break the loop

        }

        cout << "Settings Updated." << endl;
    }

    startGame(board_columns, board_rows, zombie_count);

    if (change_game_settings_numerical == 0) ///SAME SYNTAX ERROR
    {
        startGame(board_columns, board_rows, zombie_count);
    } */

}


//To change game settings, gets input from user if its a 'y' or 'n', and converts y or n to integer and then goes through if and else. y = change game settings, n = game starts like normal

int changeGameSettings (int &board_rows, int &board_columns, int &zombie_count)

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
    if (change_game_settings_numerical == 1);
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
                cout << "Enter rows => " ;
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
                cout << "Enter columns =>" ;
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

            if (zombie_count < 1) //to disallow negative values and 0. There is no such thing as month 0,-1,-2,-3,-4,...
            {
                cout << "Cannot enter 0 or numbers below that" << endl;
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

void startGame(const int &board_columns, const int &board_rows, const int &zombie_count){
    AlienZombieGameBoard playingBoard = AlienZombieGameBoard(board_columns, board_rows);

    Alien player;
    player.initPos(playingBoard);

    while (true){

        playingBoard.display();
         //gameDashboard()
        gameControl(player, playingBoard);
    }

}

//I havent finish game control and objects yet. WIP:


void gameControl(Alien &player, AlienZombieGameBoard &playingBoard){
    string userInput;
    cout << "Command> ";
    cin >> userInput;

    if(userInput == "up" || "down" || "left" || "right"){
        player.move(userInput, playingBoard);
    }else if(userInput == "arrow"){

    }else if(userInput == "help"){
        //commandHelp();
    }else if(userInput == "save"){

    }else if(userInput == "load"){

    }else if(userInput == "quit"){

    }else{
        cout << "Invalid selection, try again!";
    }
}

///Useless things:

    // cout << change_game_settings_numerical << endl; //temporary //WORKS WELL TILL HERE
    //cout << " " << endl; //actually this one considered as new page.
    //do if else statement for 1 and 0



/* void showGameSettings (const int &board_rows, const int &board_columns, const int &zombie_count)//, const string &change_game_settings)
{
    string change_game_settings;
    int change_game_settings_numerical;


    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    : " << board_rows << endl;
    cout << "Board Columns : " << board_columns << endl;
    cout << "Zombie Count  : " << zombie_count << endl;
    cout << " " << endl;
    cout << "Do you wish to change the game settings (y/n)? => ";

    while (getline(cin, change_game_settings) && !lettersOrSpaces(change_game_settings)) //Accepts only alphabets and spaces. Numbers and special characters cannot.

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
        cout << " " << endl;
        cout << "Only enter y/n!" << endl;
        cout << "                                                                       " << endl;
        cout << "Do you wish to change the game settings (y/n)? => ";
        cin >> change_game_settings;
    }


    // cout << change_game_settings << endl; //temporary //the change_game_settings variable's value is now y.

    const char* y = "y";
    const char* n = "n";

    if (change_game_settings == y)
    {
        change_game_settings_numerical = 1;
    }
    else
    {
        change_game_settings_numerical = 0;
    }


    // cout << change_game_settings_numerical << endl; //temporary //WORKS WELL TILL HERE
    cout << " " << endl; //actually this one considered as new page.
    //do if else statement for 1 and 0

} */

/* void changeGameSettings(int &board_rows, int &board_columns, int &zombie_count, const &change_game_settings_numerical)
{




    if (change_game_settings_numerical == 1)
    {
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

            //cout << board_rows; //temporary

            if (board_rows < 1) //to disallow negative values and 0. There is no such thing as month 0,-1,-2,-3,-4,...
            {
                cout << "Cannot enter 0 or numbers below that" << endl;
                cin.clear();
                cout << "Enter rows => ";
                continue;
            }
            else break; // else is to break the loop

            if (board_rows = board_rows % 2 == 0) //if the user enters an even number
            {
                cout << "Please enter an odd number!" << endl;
                cin.clear();
                cout << "Enter rows =>" ;
                continue;
            }

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

            if (board_columns < 1) //to disallow negative values and 0. There is no such thing as month 0,-1,-2,-3,-4,...
            {
                cout << "Cannot enter 0 or numbers below that" << endl;
                cin.clear();
                cout << "Enter columns => ";
                continue;
            }
            else break; // else is to break the loop

            if (board_columns = board_columns % 2 == 0) //if the user enters an even number
            {
                cout << "Please enter an odd number!" << endl;
                cin.clear();
                cout << "Enter columns =>" ;
                continue;
            }
        }

    }

    if (change_game_settings_numerical == 1)
    {
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

            if (zombie_count < 1) //to disallow negative values and 0. There is no such thing as month 0,-1,-2,-3,-4,...
            {
                cout << "Cannot enter 0 or numbers below that" << endl;
                cin.clear();
                cout << "Enter number of zombies => ";
                continue;
            }
            else break; // else is to break the loop

        }

        cout << "Settings Updated." << endl;
    }

    if (change_game_settings_numerical == 0)
    {
        cout << "game continues like normal (CHANGE THIS LATER)" << endl;
        cout << " " << endl; //temporary
    }

} */
