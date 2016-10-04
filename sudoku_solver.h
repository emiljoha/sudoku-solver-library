#ifndef SUDOKU_BACK_END_H
#define SUDOKU_BACK_END_H

#include <stdio.h>
#include <vector>
#include <iostream>
//#include "inputarea.h"

using namespace std;

class Sudoku {

public:
    // PUBLIC MEMEBER FUNCTIONS:
    // Constructor from matrix 0 for non entries. Pass puzzel as argument
    Sudoku(vector<vector<int>>);  
    
    // Solve the sudoku.
    bool solve();
    
    // read only acces to the sudoku.
    int at(int, int);
    
    //Check if sudoku is a sudoku. that is doeas the numbers already placed cause logical errors
    bool solvable();
    
    // Overloading the << operator. for printing sudoku.
    friend ostream &operator<<( ostream &output, const Sudoku &sod );

private:
    // PRIVATE MEMEBER FUNCTIONS:
    // Look for a position in the sudoku where there can be only one number.
    // fill that position with that number. Return false if failed.
    bool step1();
    // look in the same col/row/box for how many times a number is mentioned in
    // the posibilities in the cells in that col/row/box.
    bool step2();
    // Look for uniqiue doubles in row/col/box. Then delete the other numbers that
    // before was considred possible in those posittions.
    bool step3();
    // This is where it gets heavy. Find a unique double and guess and try
    // both. Continiue down one path untill solution. Possibly with more guesses.
    // If dead end reached. Go back to last cross road and try the other way.
    bool step4();
    // Now we are desperate. So even more brute force method. Do the same as step 4
    // but not for a uniqe double but for a the position with fewest posibilities.
    // And then KILL THEM ALL!!!! no, just kidding just try them all.
    bool step5();

    // guess method that handles the guessing and failure of guessing.
    // Give it the position of the two posibilites and the posible values
    bool guess(vector<vector<int> >, int, int);
    bool guess(vector<int>, int, int);
    // reset the arrrays (that save the possible numbers) as all false.
    void reset();
    // Returns vector of elementes containg the numbers that can not be in the box.
    vector<int> Check_Set(int, int);
    // Check if solved
    bool solved();
    // Update the possibilities. Return false if update failed.
    bool update();
    // Take a vector of integers between 1 and 9 and returns a list of the
    // ones not present
    vector<int> negating(vector<int>);



    // Help function to determine determinants
    vector<int> quadrant(int, int);
    // Help function to check number in cell is possible. Used when checking input sudoku.
    bool check_pos(int i, int j);

    // Search for doubletts in columns
    vector<vector<int> > doublett_col(int i, int num1, int num2);
    // Search for doubletts in row.
    vector<vector<int> > doublett_row(int j, int num1, int num2);
    // search for doubletts in box.
    vector<vector<int> > doublett_box(vector<int> Quadrant, int num1, int num2);
    // Check if there are more occurences of two numbers than the two togeter
    // in a row
    bool row_uniqe(int i, int num1, int num2);
    // in a column
    bool col_uniqe(int j, int num1, int num2);
    // in a box
    bool box_uniqe(vector<int> Q, int num1, int num2);
    // Delete numbers other than num1 and num2 in cell (i, j)
    void delete_other(int i, int j, int num1, int num2);


    // PRIVATE MEMMBER VARIABLES:
    vector<vector<int> > S;
    vector<vector<vector<int> > > M;


};

#endif // SUDOKU_BACK_END_H

