//
//  Sudoku_class.cpp
//  Sudoku
//
//  Created by Emil Johansson on 2015-10-16.
//  Copyright © 2015 Emil Johansson. All rights reserved.
//

#include "sudoku_solver.h"
#include <assert.h>

Sudoku::Sudoku(vector<vector<int> > IN_DATA){

    // Check that input is somewhat correct.
    assert(IN_DATA.size() == 9 and IN_DATA.at(0).size() == 9);

    S.resize(9);
    for (int i = 0; i < 9; i++){
        S.at(i).resize(9);
        for ( int j = 0; j < 9; j++)
            S.at(i).at(j) = IN_DATA.at(i).at(j);
    }

    M.resize(9);
    for (int i = 0; i < 9; i++)
        M.at(i).resize(9);

}


// Reset the arrrays that save the possible numbers.
void Sudoku::reset(){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++) {
            M.at(i).at(j).resize(0);
        }
    }
}

// Check a site for what possible numbers that a box can have.
vector<int> Sudoku::Check_Set(int i, int j){

    vector<int> list;

    // Check if there already is a number given to that slot. If so then
    // return the check
    if ( S.at(i).at(j) != 0){
        vector<int> temp(1);
        temp.at(0) = 10;
        return temp;
    }

    // Check for numbers in row
    for (int n = 0; n < 9; n++){
        if (n != i){
            for (int num = 1; num < 10; num++){
                if (num == S.at(n).at(j))
                    list.push_back(num);
            }
        }
    }

    // Check for numbers present in column
    for (int n = 0; n < 9; n++){
        if (n != j){
            for (int num = 1; num < 10; num++){
                if (num == S.at(i).at(n))
                    list.push_back(num);
            }
        }
    }

    vector<int> Q = quadrant(i, j);

    // Check for numbers present in Quadrant.
    for (int l = Q.at(0); l < Q.at(0) + 3; l++){
        for (int k = Q.at(1); k < Q.at(1) + 3; k++){
            if (l != i and k != j){
                for (int num = 1; num < 10; num++){
                    if (num == S.at(l).at(k))
                        list.push_back(num);
                }
            }
        }
    }
    return list;
}


// Determine the quadrant. Return the cordinates of the left top corner.
vector<int> Sudoku::quadrant(int i, int j){

    vector<int> quadrant(2);

    // Quadrant 1
    if (i < 3 and i >= 0 and j < 3 and j >= 0){
        quadrant.at(0) = 0;
        quadrant.at(1) = 0;
        return quadrant;
    }

    // Quadrant 2
    if (i < 6 and i >= 3 and j < 3 and j >= 0){
        quadrant.at(0) = 3;
        quadrant.at(1) = 0;
        return quadrant;
    }

    // Quadrant 3
    if (i < 9 and i >= 6 and j < 3 and j >= 0){
        quadrant.at(0) = 6;
        quadrant.at(1) = 0;
        return quadrant;
    }
    //---------------------------------------------

    // Quadrant 4
    if (i < 3 and i >= 0 and j < 6 and j >= 3){
        quadrant.at(0) = 0;
        quadrant.at(1) = 3;
        return quadrant;
    }

    // Quadrant 5
    if (i < 6 and i >= 3 and j < 6 and j >= 3){
        quadrant.at(0) = 3;
        quadrant.at(1) = 3;
        return quadrant;
    }

    // Quadrant 6
    if (i < 9 and i >= 6 and j < 6 and j >= 3){
        quadrant.at(0) = 6;
        quadrant.at(1) = 3;
        return quadrant;

    }

    //---------------------------------------------

    // Quadrant 7
    if (i < 3 and i >= 0 and j < 9 and j >= 6){
        quadrant.at(0) = 0;
        quadrant.at(1) = 6;
        return quadrant;
    }

    // Quadrant 8
    if (i < 6 and i >= 3 and j < 9 and j >= 6){
        quadrant.at(0) = 3;
        quadrant.at(1) = 6;
        return quadrant;
    }

    // Quadrant 9
    if (i < 9 and i >= 6 and j < 9 and j >= 6){
        quadrant.at(0) = 6;
        quadrant.at(1) = 6;
        return quadrant;
    }

    assert(false);

    vector<int> temp(2);
    temp[0] = 0; temp[1] = 0;
    return temp;
}


vector<int> Sudoku::negating(vector<int> L){
    // Handle the case when the Check_state function gives back an vector with
    // one element = 10 in the case of that there already is a number in that slot
    if (L.size() == 1 and L.at(0) == 10){
        vector<int> temp(1);
        temp.at(0) = 10;
        return temp;
    }

    vector<int> res;

    bool found = false;


    for (int num = 1; num <= 9; num++){
        for (int i = 0; i < int(L.size()); i++){
            if (L.at(i) == num){
                found = true;
                break;
            }
        }
        if (!found)
            res.push_back(num);
        found = false;
    }
    return res;
}

bool Sudoku::solve(){

    if (solved())
        return true;

    vector<int> help;


    if(!update())
        return false;

    //std::cout << *this << std::endl;

    if(!step1()){
        if(!step2()){
            while(step3()){
            }
            if(!step2()){
                if(!step4())
                    if(!step5())
                        return false;
            }
        }
    }


    // reset the posibilites
    reset();

    //std::cout << *this << std::endl;


    // solve the now sligtly more solved sudoku
    if (solve())
        return true;

    return false;
};

// Step 1
// Look for a place where there is only one posibible number and
// place that number there.
bool Sudoku::step1(){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (M.at(i).at(j).size() == 1){
                S.at(i).at(j) = M.at(i).at(j).at(0);
                return true;
            }
        }
    }
    return false;
}


// Step 2
// look in the same col/row/box for how many times a number is mentioned in the
// posibilities in the cells in that col/row/box.
// If the number can only be placed in one position in the row then place the
// number there.
bool Sudoku::step2(){

    vector<vector<int> > help;

    // check rows
    for (int num = 1; num <= 10; num++){
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                for (int n = 0; n < int(M.at(i).at(j).size()); n++){
                    if (num == M.at(i).at(j).at(n)){
                        vector<int> temp(2); temp[0] = i; temp[1] = j;
                        help.push_back(temp);
                    }
                }
            }
            if (help.size() == 1){
                S.at(help.at(0).at(0)).at(help.at(0).at(1)) = num;
                return true;
            }
            help.clear();
        }
    }

    // check columns
    for (int num = 1; num <= 10; num++){
        for (int j = 0; j < 9; j++){
            for (int i = 0; i < 9; i++){
                for (int n = 0; n < int(M.at(i).at(j).size()); n++){
                    if (num == M.at(i).at(j).at(n)){
                        vector<int> temp(2);
                        temp.at(0) = i;
                        temp.at(1) = j;
                        help.push_back(temp);
                    }
                }
            }
            if (help.size() == 1){
                S.at(help.at(0).at(0)).at(help.at(0).at(1)) = num;
                return true;
            }
            help.clear();
        }
    }


    // check boxes
    vector<int> temp(2); temp[0] = 0; temp[1] = 0;
    for (vector<int> Q = temp; Q.at(0) <= 6; Q.at(0) = Q.at(0) + 3){
        for ( ; Q.at(1) <= 6; Q.at(1) = Q.at(1) + 3){
            for (int num = 1; num <= 10; num++){
                for (int j = Q.at(0); j < Q.at(0) + 3; j++){
                    for (int i = Q.at(1); i < Q.at(1) + 3; i++){
                        for (int n = 0; n < int(M.at(i).at(j).size()); n++){
                            if (num == M.at(i).at(j).at(n))
                                vector<int> temp(2); temp[0] = i; temp[1] = j;
                                help.push_back(temp);
                        }
                    }
                }

                if (help.size() == 1){
                    S.at(help.at(0).at(0)).at(help.at(0).at(1)) = num;
                    return true;
                }
            }
        }
    }



    return false;
}


// Step 3
// Look for uniqiue doubles in row/col/box. Then delete the other numbers that
// before was considred possible in those posittions.
bool Sudoku::step3(){
    // Did step3 do any good?
    // bool succes = false;
    // help vector to save positions of potential doubles.
    vector<vector<int> > help;

    // Check columns
    for (int num1 = 1; num1 <= 9; num1++){
        for (int num2 = num1 + 1; num2 <= 9; num2++){
            // Check so that num1 is not equal to num2
            if (num1 != num2){

                // loop over the columns
                for (int i = 0; i < 9; i++){

                    help = doublett_col(i, num1, num2);
                    if (help.size() == 2){
                        if (col_uniqe(i, num1, num2)){
                            if (M.at(help.at(0).at(0)).at(help.at(0).at(1)).size() != 2 or
                                M.at(help.at(1).at(0)).at(help.at(1).at(1)).size() != 2){
                                delete_other(help.at(0).at(0), help.at(0).at(1), num1, num2);
                                delete_other(help.at(1).at(0), help.at(1).at(1), num1, num2);
                                assert(M.at(help.at(0).at(0)).at(help.at(0).at(1)).size() >= 2 and
                                       M.at(help.at(1).at(0)).at(help.at(1).at(1)).size() >= 2);
                                return true;
                            }

                        }
                    }
                }
            }
        }
    }

    help.clear();

    // Check rows
    for (int num1 = 1; num1 <= 9; num1++){
        for (int num2 = num1 + 1; num2 <= 9; num2++){
            // Check so that num1 is not equal to num2
            if (num1 != num2){

                // loop over the rows
                for (int j = 0; j < 9; j++){

                    help = doublett_row(j, num1, num2);
                    if (help.size() == 2){
                        if (row_uniqe(j, num1, num2)){
                            if (M.at(help.at(0).at(0)).at(help.at(0).at(1)).size() != 2 or
                                M.at(help.at(1).at(0)).at(help.at(1).at(1)).size() != 2){
                                delete_other(help.at(0).at(0), help.at(0).at(1), num1, num2);
                                delete_other(help.at(1).at(0), help.at(1).at(1), num1, num2);
                                assert(M.at(help.at(0).at(0)).at(help.at(0).at(1)).size() >= 2 and
                                       M.at(help.at(1).at(0)).at(help.at(1).at(1)).size() >= 2);
                                return true;
                            }

                        }
                    }
                }
            }
        }
    }


    help.clear();

    // Check Boxes
    for (int num1 = 1; num1 <= 9; num1++){
        for (int num2 = num1 + 1; num2 <= 9; num2++){
            // Check so that num1 is not equal to num2
            if (num1 != num2){

                // loop over the boxes
                vector<int> temp(2); temp[0] = 0; temp[1] = 0;
                for (vector<int> Q = temp; Q.at(0) < 9;  Q.at(0) = Q.at(0) + 3){
                    for( ;Q.at(1) < 9; Q.at(1) = Q.at(1) + 3){

                        help = doublett_box(Q, num1, num2);
                        if (help.size() == 2){
                            if (box_uniqe(Q, num1, num2)){
                                if (M.at(help.at(0).at(0)).at(help.at(0).at(1)).size() != 2 or
                                    M.at(help.at(1).at(0)).at(help.at(1).at(1)).size() != 2){
                                    delete_other(help.at(0).at(0), help.at(0).at(1), num1, num2);
                                    delete_other(help.at(1).at(0), help.at(1).at(1), num1, num2);
                                    return true;
                                    assert(M.at(help.at(0).at(0)).at(help.at(0).at(1)).size() >= 2 and
                                           M.at(help.at(1).at(0)).at(help.at(1).at(1)).size() >= 2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    return false;
}

// Step 4
// If everything else fail. Look for a uniqie double. When found create a Guess
// object and append to a vector that stores that guess in the order they have
// been made. Follow down one of the paths like normal with the solve routine.
// If there is a dead end an exeption will be trown. This will be caught by the
// function call that made the latest guess. The Guess object will be checked to see
// if both ways have been tried of so it throws another exeption to be caught by the
// next guess made witch has then wrong. And so on...

bool Sudoku::step4(){

    vector<vector<int> > help;

    // Check columns
    for (int num1 = 1; num1 <= 9; num1++){
        for (int num2 = num1 + 1; num2 <= 9; num2++){
            // Check so that num1 is not equal to num2
            if (num1 != num2){

                // loop over the columns
                for (int i = 0; i < 9; i++){

                    help = doublett_col(i, num1, num2);
                    if (help.size() == 2){
                        if (col_uniqe(i, num1, num2)){
                            if (M.at(help.at(0).at(0)).at(help.at(0).at(1)).size() != 2 or
                                M.at(help.at(1).at(0)).at(help.at(1).at(1)).size() != 2){
                                delete_other(help.at(0).at(0), help.at(0).at(1), num1, num2);
                                delete_other(help.at(1).at(0), help.at(1).at(1), num1, num2);
                            }
                            if(guess(help, num1, num2)){
                                return true;
                            }
                            return false;

                        }
                    }
                }
            }
        }
    }

    help.clear();

    // Check rows
    for (int num1 = 1; num1 <= 9; num1++){
        for (int num2 = num1 + 1; num2 <= 9; num2++){
            // Check so that num1 is not equal to num2
            if (num1 != num2){

                // loop over the rows
                for (int j = 0; j < 9; j++){

                    help = doublett_row(j, num1, num2);
                    if (help.size() == 2){
                        if (row_uniqe(j, num1, num2)){
                            if (M.at(help.at(0).at(0)).at(help.at(0).at(1)).size() != 2 or
                                M.at(help.at(1).at(0)).at(help.at(1).at(1)).size() != 2){
                                delete_other(help.at(0).at(0), help.at(0).at(1), num1, num2);
                                delete_other(help.at(1).at(0), help.at(1).at(1), num1, num2);
                            }
                            if(guess(help, num1, num2)){
                                return true;
                            }
                            return false;

                        }
                    }
                }
            }
        }
    }


    help.clear();

    // Check Boxes
    for (int num1 = 1; num1 <= 9; num1++){
        for (int num2 = num1 + 1; num2 <= 9; num2++){
            // Check so that num1 is not equal to num2
            if (num1 != num2){

                // loop over the boxes
                vector<int> temp(2); temp[0] = 0; temp[1] = 0;
                for (vector<int> Q = temp; Q.at(0) < 9;  Q.at(0) = Q.at(0) + 3){
                    for( ;Q.at(1) < 9; Q.at(1) = Q.at(1) + 3){

                        help = doublett_box(Q, num1, num2);
                        if (help.size() == 2){
                            if (box_uniqe(Q, num1, num2)){
                                if (M.at(help.at(0).at(0)).at(help.at(0).at(1)).size() != 2 or
                                    M.at(help.at(1).at(0)).at(help.at(1).at(1)).size() != 2){
                                    delete_other(help.at(0).at(0), help.at(0).at(1), num1, num2);
                                    delete_other(help.at(1).at(0), help.at(1).at(1), num1, num2);
                                }
                                if(guess(help, num1, num2)){
                                    return true;
                                }
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

return false;

}

// Step 5
// Now we are kinda desperate. Lets try find a position with 2 posiblities and try them
// both and se witch works. IF there is no position with 2 posibilites find one
// with 3 and so on.
bool Sudoku::step5(){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++) {
            if (M.at(i).at(j).size() == 2){
                vector<int> temp(2); temp[0] = i; temp[1] = j;
                if (guess(temp, M.at(i).at(j).at(0), M.at(i).at(j).at(1)))
                    return true;

                return false;
            }
        }
    }
    return false;
}

ostream &operator<<( ostream &output, const Sudoku &sod ){
    for (int j = 0; j < 9; j++){
        for (int i = 0; i < 9; i++){
            if (sod.S.at(i).at(j) == 0){
                output << " " << " ";
            }
            else{
                output << sod.S.at(i).at(j) << " ";
            }
        }
        output << "\n";
    }
    return output;
};


// Search for doubletts in columns
vector<vector<int> > Sudoku::doublett_col(int i, int num1, int num2){

    bool is_num1 = false, is_num2 = false;

    vector<vector<int> > help;
    for (int j = 0; j < 9; j++){
        for (int k = 0; k < int(M.at(i).at(j).size()); k++){
            if (M.at(i).at(j).at(k) == num1)
                is_num1 = true;
            if (M.at(i).at(j).at(k) == num2)
                is_num2 = true;
        }
        if (is_num1 and is_num2){
            vector<int> temp(2); temp[0] = i; temp[1] = j;
            help.push_back(temp);
        }
        is_num1 = false;
        is_num2 = false;
    }
    vector<vector<int> > temp(0);

    if (help.size() == 2)
        return help;
    else return temp;
 }


// Search for doubletts in row.
vector<vector<int> > Sudoku::doublett_row(int j, int num1, int num2){
    bool is_num1 = false, is_num2 = false;

    vector<vector<int> > help;
    for (int i = 0; i < 9; i++){
        for (int k = 0; k < int(M.at(i).at(j).size()); k++){
            if (M.at(i).at(j).at(k) == num1)
                is_num1 = true;
            if (M.at(i).at(j).at(k) == num2)
                is_num2 = true;
        }
        if (is_num1 and is_num2){
            vector<int> temp(2); temp[0] = i; temp[1] = j;
            help.push_back(temp);
        }
        is_num1 = false;
        is_num2 = false;
    }
    vector<vector<int> > temp;
    if (help.size() == 2)
        return help;
    else return temp;
};


// search for doubletts in box.
vector<vector<int> > Sudoku::doublett_box(vector<int> Q, int num1, int num2){
    bool is_num1 = false, is_num2 = false;

    vector<vector<int> > help;
    for (int i = Q.at(0); i < Q.at(0) + 3; i++){
        for (int j = Q.at(1); j < Q.at(1) + 3; j++){

            for (int k = 0; k < int(M.at(i).at(j).size()); k++){
                if (M.at(i).at(j).at(k) == num1)
                    is_num1 = true;
                if (M.at(i).at(j).at(k) == num2)
                    is_num2 = true;
            }
            if (is_num1 and is_num2){
                vector<int> temp(2); temp[0] = i; temp[1] = j;
                help.push_back(temp);
            }
            is_num1 = false;
            is_num2 = false;
        }
    }
    vector<vector<int> > temp;
    if (help.size() == 2)
    return help;
    else return temp;
}


// Check if there are more occurences of two numbers than the two togeter
// in a row
bool Sudoku::row_uniqe(int j, int num1, int num2){
    bool is_num1 = false, is_num2 = false;

    for (int i = 0; i < 9; i++){
        for (int k = 0; k < int(M.at(i).at(j).size()); k++){
            if (M.at(i).at(j).at(k) == num1)
                is_num1 = true;
            if (M.at(i).at(j).at(k) == num2)
                is_num2 = true;
        }
        if ((is_num1 or is_num2) and !(is_num1 and is_num2)){
            return false;
        }
        is_num1 = false;
        is_num2 = false;
    }

    return true;
};


// in a column
bool Sudoku::col_uniqe(int i, int num1, int num2){
    bool is_num1 = false, is_num2 = false;

    for (int j = 0; j < 9; j++){
        for (int k = 0; k < int(M.at(i).at(j).size()); k++){
            if (M.at(i).at(j).at(k) == num1)
                is_num1 = true;
            if (M.at(i).at(j).at(k) == num2)
                is_num2 = true;
        }
        if ((is_num1 or is_num2) and !(is_num1 and is_num2))
            return false;
        is_num1 = false;
        is_num2 = false;
    }

    return true;
};


// in a box
bool Sudoku::box_uniqe(vector<int> Q, int num1, int num2){
    bool is_num1 = false, is_num2 = false;

    for (int i = Q.at(0); i < Q.at(0) + 3; i++){
        for (int j = Q.at(1); j < Q.at(1) + 3; j++){

            for (int k = 0; k < int(M.at(i).at(j).size()); k++){
                if (M.at(i).at(j).at(k) == num1)
                    is_num1 = true;
                if (M.at(i).at(j).at(k) == num2)
                    is_num2 = true;
            }
            if ((is_num1 or is_num2) and !(is_num1 and is_num2))
                return false;
            is_num1 = false;
            is_num2 = false;
        }
    }
    return true;
};

// Delete numbers other than num1 and num2 in cell (i, j)
void Sudoku::delete_other(int i, int j, int num1, int num2){
    for (int k = 0; k < int(M.at(i).at(j).size()); k++){
        if( M.at(i).at(j).at(k) != num1 and M.at(i).at(j).at(k) != num2 )
            M.at(i).at(j).erase(M.at(i).at(j).begin() + k);
    }
    assert(M.at(i).at(j).size() >= 2);
};

bool Sudoku::solved(){
    // Check if completeley solved. If so end function
    int filled = 0;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (S.at(i).at(j) != 0)
                filled++;
        }
    }

    if (filled == 81){
        return true ;
    }
    return false;
}

bool Sudoku::update(){
    vector<int> help;
    // Update the posible numbers in all positions
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            help = negating(Check_Set(i, j));
            if(help.size() == 0)
                return false;
            if (help.at(0) != 10){
                M.at(i).at(j) = help;
            }
        }
    }
    return true;
}

// guess method that handles the guessing and failure of guessing.
// Give it the position of the two posibilites and the posible values
bool Sudoku::guess(vector<vector<int> > pos, int num1, int num2){
    vector<vector<int> > MEM = this->S;

    S.at(pos.at(0).at(0)).at(pos.at(0).at(1)) = num1;
    S.at(pos.at(1).at(0)).at(pos.at(1).at(1)) = num2;

    if (solve())
        return true;

    this->S = MEM;

    S.at(pos.at(0).at(0)).at(pos.at(0).at(1)) = num2;
    S.at(pos.at(1).at(0)).at(pos.at(1).at(1)) = num1;


    if (solve())
        return true;

    this->S = MEM;

    return false;
}

bool Sudoku::guess(vector<int> pos, int num1, int num2){
    vector<vector<int> > MEM = this->S;

    S.at(pos.at(0)).at(pos.at(1)) = num1;

    if (solve())
        return true;

    this->S = MEM;

    S.at(pos.at(0)).at(pos.at(1)) = num2;


    if (solve())
        return true;

    this->S = MEM;

    return false;
}

// read only acces to the sudoku.
int Sudoku::at(int i, int j){
    return S.at(i).at(j);
}

bool Sudoku::check_pos(int i, int j){
    if (at(i, j) != 0){
        // check column
        for (int k = 0; k < 9; k++){
            if (k != j){
                if (at(i, k) == at(i, j))
                    return false;
            }
        }
        // check rows
        for (int k = 0; k < 9; k++){
            if (k != i){
                if (at(k, j) == at(i, j))
                    return false;
            }
        }

        // check box
        vector<int> Q = quadrant(i, j);
        for (int k = Q[0]; k < Q[0] + 3; k++){
            for (int l = Q[1]; l < Q[1] + 3; l++){
                if (k != i and l != j){
                    if (at(i, j) == at(k, l))
                        return false;
                }
            }
        }
    }
    return true;
}

bool Sudoku::solvable(){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(!check_pos(i, j))
                return false;
        }
    }
    return true;
}



