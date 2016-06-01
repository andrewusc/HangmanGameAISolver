#include <cstdlib>
#include <iostream>
#include <fstream>  
#include <string>
#include <vector>
#include <list>
#include "Hangman.h"
using namespace std;

int main(int argc, char *argv[])
{
    /* for testing */
    if(argc <= 1){ 
	     cout << "Please input commend-line parameter." << endl;
	     return 0;
    }
    string target = argv[1];
    ifstream in("dict.txt");  
    if (! in.is_open())  { 
        cout << "Error opening file"; 
        exit (1); 
    }  
    
    Hangman hangman(target, in);
    hangman.showBoard();
    hangman.trainingBrain();
    while(!hangman.validBoard()){
        char* ch = new char(char(0));
        if(!hangman.guess(ch))
				hangman.trainingBrain();  // Delete words with char 'ch'.
        else{
			    hangman.adjustFreq(ch);     // Delete all words cannot match the current board.
        }
		if(hangman.getFailTimes() >= hangman.MAX_FAILS){
  		        cout << "You Failed! Please Try Again." << endl;
  		        cout << "Target word is " << target << endl;
  		        break; 
 	    }	  				 
	}
    if(hangman.validBoard()){
		cout << "You Win!" << endl; 		 
    }

   /* list<string>::iterator wordsIter;
    for(wordsIter = hangman.words.begin(); wordsIter != hangman.words.end(); wordsIter++){
		  cout << *wordsIter << endl;	  
    } */
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
