#include "6.1 Settings.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime> // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
using namespace std;

class AlienZombie
{
private:
    vector< vector<char> > map_; // convention to put trailing underscore
    int board_rows_, board_columns_; // to indicate private data

public:
    AlienZombie(int board_rows , int board_columns );
    void init(int board_rows, int board_columns);
    void display() const;
};

AlienZombie::AlienZombie(int board_rows, int board_columns)
{
    init(board_rows, board_columns);
}

void AlienZombie::init(int board_rows, int board_columns)
{
    board_rows_ = board_rows;
    board_columns_ = board_columns;

    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int noOfObjects = 10; // number of objects in the objects array

    // create dynamic 2D array using vector
    map_.resize(board_columns_); // create empty rows
    for (int i = 0; i < board_columns_; ++i)
    {
        map_[i].resize(board_rows_); // resize each row
    }

    // put random characters into the vector array
    for (int i = 0; i < board_columns_; ++i)
    {
        for (int j = 0; j < board_rows_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

void AlienZombie::display() const
{
    // comment this out during testing
    // system("cls"); // OR system("clear"); for Linux / MacOS


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
        cout << setw(2) << (board_columns_ - i);

        // display cell content and border of each column
        for (int j = 0; j < board_rows_; ++j)
        {
            cout << "|" << map_[i][j];
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



