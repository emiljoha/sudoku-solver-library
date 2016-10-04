#include <iostream>
#include "sudoku_solver.h"

using namespace std;

int main(){

    /* Test of the library with a "hard" puzzel from the guardian
     https://www.theguardian.com/lifeandstyle/2013/dec/12/sudoku-2680-hard 
    */ 
    
    std::vector<std::vector<int> > puzzel = {{0, 0, 0, 0, 3, 7, 6, 0, 0},
   			         {0, 0, 0, 6, 0, 0, 0, 9, 0},
   			         {0, 0, 8, 0, 0, 0, 0, 0, 4},
   			         {0, 9, 0, 0, 0, 0, 0, 0, 1},
   			         {6, 0, 0, 0, 0, 0, 0, 0, 9},
   			         {3, 0, 0, 0, 0, 0, 0, 4, 0},
   			         {7, 0, 0, 0, 0, 0, 8, 0, 0},
				 {0, 1, 0, 0, 0, 9, 0, 0, 0},
				 {0, 0, 2, 5, 4, 0, 0, 0, 0}};
    
    Sudoku s(puzzel);
    std::cout << s << endl;
    s.solve(); 
    std::cout << s; 
}
