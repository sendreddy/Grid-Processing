/* Name       : Srujana Endreddy 
 * Date       : September 20, 2022 
 * File Name  : Project1.cpp 
 * Description: This program will import given grid text data files containing a grid of letters for a Word Search puzzle. The grid letters 
  in the puzzle are organized in a two-dimensional grid; however, in this program it is stored in a one-dimensional grid. The programs reads
  a grid of 2D letters from a given grid text file and then saves it a 1D input array. To store the matching results, a new output 1D array is
  created. The grid of letters from the grid text file in the puzzle are printed to the terminal as a 2D array. Then from the command line, 
  the user writes a list of words for the program to search in a specific grid text file. When ran successfully, the searched words
  will be found and the program will print the grid of letters to the console. */ 

#include <iostream>
#include <fstream>
#include <string> 

using namespace std; 

//Globals 
char* input; 
int nrows;
int ncols; 
char* output;  //declared new output array pointer 



//Initialize a new Word search game given a file and init char 
/*This function first checks if given grid file was opened correctly or not. It then reads the size of the grid
(which is the rows and columns) and stores it in char input variable. After, with the help of a loop it reads
all chars into the input array. */
bool initGame(string filename) {
    ifstream fin (filename);   //This file input stream that will be used to read the size of the grid from the file.

    
 // Check file was found 
if (!fin.is_open()) {
cout << filename << "not found" << endl;  
return false;      
}

//this reads the size of the grid
fin >> nrows;
fin >> ncols;

input = new char[nrows*ncols];    //read the rows and columns ex: 5 by 5 or 10 by 15         
output = new char[nrows*ncols];   //read the rows and columns ex: 5 by 5 or 10 by 15        

 //Loop to read all chars 
for (int i = 0; i < nrows*ncols; ++i) {
    fin >> input[i];
    output[i] = '-'; 
}

return true; 

}


/*This function prints the grid. It loops over nrows and ncols to print each char in the grid file to the terminal as 
two-dimensional grid. */
void printGrid(char grid[]) {

  //Nested for-loop to print input grid from each given row
  for (int r = 0; r < nrows; ++r) {    
    for (int c = 0; c < ncols; ++c) {  //from lab1
      int i = r*ncols + c; 
      cout << grid[i] << " "; 
  }
    cout << endl; 

  }

}


/*This function searches for a word in all 8 directions. The function loops over all chars in the word. Under three circumstances, 
the word match will fail in one of the three ways; the if statement is implemented to display this. When all three tests pass, 
r and c are incremented and will continue the loop on to the next character. In the end, the word will only match when the loop 
completes without any errors, then it returns true.
*/
bool isWordAtInput(string word, int r, int c, int rincr, int cincr) {
  for (int  i = 0; i < word.length(); i++) {
     if (c < 0 || c >= ncols || r < 0 || r >= nrows || word[i] != input[r*ncols+c]) {  //word match fails in 1 of 3 ways 
           return false; 
      }
        r += rincr;  //increment r if all 3 tests pass
        c += cincr;  //increment c if all 3 tests pass 

   }

      return true; 

}



//In this function, if a word is found in the input grid then the word's letters should be set in the output grid at the same location. 
void setWordAtOutput(string word, int r, int c, int rincr, int cincr) {
   for (int i = 0; i < word.length(); ++i) {
     char a = word.at(i); 
     output[r*ncols+c] = a; //set the word character in the output grid location 
     r = r + rincr;  //sometimes r may not increment, hence use this instead of r++ because this means it always increments 
     c += cincr;     //increment c 
   }

}


/*This function searches for the word in the grid in all eight directions. A nested for-loop is implemented to loop over all 
rows and columns. */  
void findWord(string word) {
   for (int r = 0; r < nrows; ++r) {
     for (int c = 0; c < ncols; ++c) {
         if (isWordAtInput(word, r, c, 0, -1)) { setWordAtOutput(word, r, c, 0, -1);} //going left 
         if (isWordAtInput(word, r, c, 0,  1)) { setWordAtOutput(word, r, c, 0, 1); } //going right 
         if (isWordAtInput(word, r, c, -1, 0)) { setWordAtOutput(word, r, c,-1, 0); } //going up
         if (isWordAtInput(word, r, c, 1,  0)) { setWordAtOutput(word, r, c, 1, 0); } //going down
         if (isWordAtInput(word, r, c, -1,-1)) { setWordAtOutput(word, r, c,-1, -1);} //going up and left 
         if (isWordAtInput(word, r, c, -1, 1)) { setWordAtOutput(word, r, c,-1, 1); } //going up and right 
         if (isWordAtInput(word, r, c, 1, -1)) { setWordAtOutput(word, r, c, 1, -1);} //going down and left 
         if (isWordAtInput(word, r, c, 1,  1)) { setWordAtOutput(word, r, c, 1, 1); } //going down and right 
      }
    }   
   }



// > c++ Project1.cpp -o play 
// > play grid2.txt HELLO WORLD 
//Given main method 
int main(int argc, char* argv[]) { 
    string filename(argv[1]); 
 
    if (!initGame(filename)) { return -1; } 
    printGrid(input); 
 
    for (int i=2; i<argc; ++i) { 
        string word(argv[i]); 
        cout << "Searching for " << word << endl; 
        findWord(word); 
    } 
 
    printGrid(output); 
    delete[] input; 
    delete[] output; 
} 

