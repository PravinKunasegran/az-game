#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;


//to only accept alphabetical letters/space:
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

main ()
{

    //first let me define the variables
    int board_rows;
    int board_columns;
    int zombie_count;
    string change_game_settings; //does the user want to change game settings? (y/n)
    //these 4 variables' value will be determined by the user
    int change_game_settings_numerical; //this one for later, if its y, it is 1. if its n, it is 0.

    //DEFAULT GAME SETTINGS

    board_rows = 5;
    board_columns = 9;
    zombie_count = 1;

    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    : " << board_rows << endl;
    cout << "Board Columns : " << board_columns << endl;
    cout << "Zombie Count  : " << zombie_count << endl;
    cout << " " << endl;
    cout << "Do you wish to change the game settings (y/n)? => ";


    while (getline(cin,change_game_settings) && !lettersOrSpaces(change_game_settings)) //Accepts only alphabets and spaces. Numbers and special characters cannot.


    {
        cout << "                                                                       " << endl;
        cout << "no numbers or special characters!" << endl;
        cout << "                                                                       " << endl;
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
    }

    //TEMPORARY, PLEASE REMOVE THIS LATER

    cout << "board rows: " << board_rows << endl;
    cout << "board columns: " << board_columns << endl;
    cout << "zombie count: " << zombie_count << endl;

}