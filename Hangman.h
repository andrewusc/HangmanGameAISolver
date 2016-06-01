
#ifndef __HangmanGame__Hangman__
#define __HangmanGame__Hangman__

#include <stdio.h>
#include <string>
#include <list>
#include <cstdlib>
#include <iostream>
#include <fstream>  
using namespace std;

struct Dict{
     char ch;
     int freq;
};

class Hangman{
public:
    Hangman(string target,ifstream& in);
    bool guess(char *ch);
    void showBoard();
    bool trainingBrain();
    bool validBoard();
    void adjustFreq(char *ch);
    int getFailTimes() const;
    
    static const int MAX_FAILS = 6;
private:
    int failTimes;
    string missedWords;
    string currBoard;
    string correctWord;
    list<string> words;
    struct Dict dict[256];

	
    
    
};

#endif /* defined(__HangmanGame__Hangman__) */
