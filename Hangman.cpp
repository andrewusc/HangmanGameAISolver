#include "Hangman.h"
#include <string.h>
#include <iostream>
using namespace std;

Hangman::Hangman(string target,ifstream& in ){
    failTimes = 0;
    missedWords = "";
    correctWord = target;
    currBoard = "";
    for(int i = 0; i < target.size(); i++){
        currBoard += '_';
    }
    for(int i = 0; i < 256; i++){
        dict[i].ch = char(i);
        dict[i].freq = 0;         
    } 
    char buffer[256];
    while (!in.eof()){  
       in.getline (buffer,255);  
       if(strlen(buffer) == target.size())
            words.push_back(buffer);
    } 
}


void Hangman::showBoard(){
     cout << currBoard[0];
     
     for(int i = 1; i < currBoard.size(); i++){
          cout<< " " << currBoard[i];
     }
	 cout << "  " << "missed: ";
	 if(missedWords.size() > 0)  cout << missedWords[0];
	 for(int i = 1; i < missedWords.size(); i++){
	       cout << "," << missedWords[i];
	 }
	 cout << endl;
}

bool Hangman::validBoard(){
     return currBoard == correctWord;
}

int Hangman::getFailTimes() const{
	 return failTimes;
}

bool Hangman::guess(char* ch){
     int maxNum = INT_MIN, maxChar = 0;
     for(int i = 0; i < 256; i++){  
          if(maxNum < dict[i].freq){
  			   maxNum = dict[i].freq;
  			   maxChar = i;
		  }  
	 }
     *ch = char(maxChar);
     cout << endl << "guess:" << (char)maxChar << endl;
     
     
     // update currBoard and missedWord
     bool flag = false;
     for(int i = 0; i < correctWord.size(); i++){
         if(correctWord[i] == *ch || correctWord[i] == char(*ch+('A'-'a'))){
              flag = true;
              currBoard[i] = correctWord[i];
         }
     }
     if(!flag){
          missedWords += *ch;
          failTimes++;
          trainingBrain();
          //cout << missedWords << endl;
     }
     showBoard();
     return flag;
}


bool Hangman::trainingBrain(){
    for(int i = 0; i < 256; i++){  // reset dict.
        dict[i].freq = 0;         
    } 
    list<string>::iterator wordsIter;
    for(wordsIter = words.begin(); wordsIter != words.end(); wordsIter++){
		  string str = *wordsIter;
          bool exist[256] = {false};
          
          for(int i = 0; i < str.size(); i++){       // hash each letter
                char c = str[i];
                if(c >= 'A' && c <= 'Z'){
					 exist[c-('A'-'a')] = true;
			    }
				else exist[c] = true;
          }
          bool flag = false;
          for(int i = 0; i < missedWords.size(); i++){
		        char mc = missedWords[i];
                if(exist[mc]){
		              wordsIter--;
                      words.remove(str);    
                      flag = true;
                      break;
                }  
          }
          if(flag){ continue; }
          
     /*     for(int i = 0; i < currBoard.size(); i++){
		  		if(currBoard[i] == '_')  continue;  
		        char ch1 = currBoard[i];
		        char ch2 = str[i];
		        if(ch1 >= 'A' && ch1 <= 'Z') ch1 =- ('A' - 'a');
		        if(ch2 >= 'A' && ch2 <= 'Z') ch2 =- ('A' - 'a');
		        if(ch1 != ch2){
   				      wordsIter--;
                      words.remove(str);    
                      flag = true;
                      break;
	   			} 
		  }
          if(flag){ continue; }   */
          
          for(int i = 0; i < 256; i++){
                if(exist[i])   dict[i].freq++;
          }
    }
    for(int i = 0; i < currBoard.size(); i++){
		  char ch = currBoard[i];
		  if(ch != '_'){
	   	  		dict[ch].freq = 0;
				if(ch >= 'a' && ch <= 'z'){
		  			  dict[ch+('A'-'a')].freq = 0;
		        }
		        else if(ch >= 'A' && ch <= 'Z'){
					  dict[ch-('A'-'a')].freq = 0;
			    }
		  }   
    }
    
    return true;
}

void Hangman::adjustFreq(char *guss){      
    //dict[*guss].freq = 0;  
    for(int i = 0; i < 256; i++){  // reset dict.
        dict[i].freq = 0;         
    }
    
    list<string>::iterator wordsIter;
    for(wordsIter = words.begin(); wordsIter != words.end(); wordsIter++){
		  string str = *wordsIter;
          bool exist[256] = {false};
          
          for(int i = 0; i < str.size(); i++){       // hash each letter
                char c = str[i];
                if(c >= 'A' && c <= 'Z'){
					 exist[c-('A'-'a')] = true;
			    }
				else exist[c] = true;
          }
          bool flag = false;
          
          for(int i = 0; i < currBoard.size(); i++){
		  		if(currBoard[i] == '_')  continue;  
		        char ch1 = currBoard[i];
		        char ch2 = str[i];
		        if(ch1 >= 'A' && ch1 <= 'Z') ch1 =- ('A' - 'a');
		        if(ch2 >= 'A' && ch2 <= 'Z') ch2 =- ('A' - 'a');
		        if(ch1 != ch2){
   				      wordsIter--;
                      words.remove(str);    
                      flag = true;
                      break;
	   			}
		  }
          if(flag){ continue; } 
          
          for(int i = 0; i < 256; i++){
                if(exist[i])   dict[i].freq++;
          }
    }
    
    for(int i = 0; i < currBoard.size(); i++){
		  char ch = currBoard[i];
		  if(ch != '_'){
	   	  		dict[ch].freq = 0;
				if(ch >= 'a' && ch <= 'z'){
		  			  dict[ch+('A'-'a')].freq = 0;
		        }
		        else if(ch >= 'A' && ch <= 'Z'){
					  dict[ch-('A'-'a')].freq = 0;
			    }
		  }   
    }
}
