# HangmanGameAISolver
A smart solver of Hangman Game based on Bayes' theorem.

0)A simple introduction of HangmanGame on Wiki: 
https://en.wikipedia.org/wiki/Hangman_(game)

1)Have a try:
http://www.playhangman.com/


2)The word to be tested is passed by commend-line argument. 

3)Ideas:

0. The first classifier is the length of the testing word.
1. The first guess is the letter of the highest frequency. If we miss, we just simply try again.
2. The subsequent guesses are based on the probabilities of each letter adjusted according to the Bayes' Theorem.
   Actually, it's conditional probability. We calculate the distribution of the letters based on independent events after we remove the impossible words.(i.e., if we don't get a match, we remove all possible words that don't contain that letter (and all previous suggested letters) The next guess should be the most popular letter. 
3. We have six chances to do the incorrect guesses.

