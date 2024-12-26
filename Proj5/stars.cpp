#include <iostream>
#include <cctype> //to use islower()
#include <iomanip> //to use setprecision
#include <cstring> //to use cstring functins like strcpy
#include "utilities.h" //file with randint() and getwords()
using namespace std;

/*command to run in VSCode: 
g++ stars.cpp utilities.cpp -o stars
./stars 
*/

/*
Test words:
3 letter: cat
4 letter bad: wint
4 letter good: pint
5 letter bad: winte
5 letter good: pique
6 letter bad: phones
6 letter good: pinkie
7 letter: winters
*/

void starsandplanets(const char secretWord[], char guessWord[]){ //function to count stars and planets
    int starcount=0;
    int planetcount=0;
    char copy[7];
    strcpy(copy, secretWord);
    
    // examples:
    // plot and bobby
    // bobby and plot
    // plot and plot
    
    int swSize = strlen(secretWord);
    int gwSize = strlen(guessWord);

    //stars
    for(int i=0; (i<swSize)&&(i<gwSize); i++){
        if(secretWord[i]==guessWord[i] && i<swSize){
            starcount++;
            copy[i]='*';
        }
    }

    //planets
    for(int i=0; i<gwSize;i++){
        if (i < swSize && guessWord[i] == secretWord[i]) {
            continue;
        }

        for (int j=0; j<strlen(secretWord); j++){
            if(guessWord[i]==copy[j]){
                planetcount++;
                copy[j]='*';
                break;
        }
        }
    }
    cout <<"Stars: "<<starcount<<", Planets: "<<planetcount<<endl;
}

int runOneRound(const char words[][7], int nWords, int wordnum){ //required function
    bool correctGuess=false; //flag to end program asking for guesses
    bool contains=false; //used as a flag to see if the word is contained in wordlist
    char trialWord[100]; //has to be 4 to 6 chars. In other words, null char '/0' at positions 4, 5, or 6
    int trialWordSize =0;
    int tries=0;

    if(nWords<=0 || wordnum<0 || wordnum>=nWords){ //basic error checking as specified by the spec
        return -1;
    }

    while(!correctGuess){
          cout << "Trial word: ";
          cin.getline(trialWord, 101, '\n');
          //cerr << "the input was: " << trialWord<<endl; //print statement to debug

          trialWordSize=strlen(trialWord);
          if(trialWordSize<4 || trialWordSize>6){ //if word size is less than 4 chars or greater than 6 chars it doesn't count towards guesses
            cout << "Your trial word must be a word of 4 to 6 lower case letters.\n";
            continue;
          }

          bool valid=true;
          for(int i=0; i<trialWordSize;i++){
            if(!islower(trialWord[i])){//if trialWord doesn't contain valid characters, it does not count toward guesses
                cout << "Your trial word must be a word of 4 to 6 lower case letters.\n";
                valid=false;
                break;
            }
          }
          if(!valid){ //if non lowercase letter was found in trialWord cstring is not valid
            continue;
          }
          
          contains=false; //resetting flag variable
          for (int i=0; i<nWords; i++){
            if(!(strcmp(trialWord, words[i]))){ //if trialWord matches a word in the wordList, it is contained
                contains=true;
            }
          }
          if(!contains){ //if not contained, program outputs I don't know
            cout << "I don't know that word.\n";
            continue;
          }

          if(!(strcmp(trialWord, words[wordnum]))){
            tries++;
            return tries;
         }
         else{
            //cerr << "something something stars and planets\n";
            starsandplanets(words[wordnum], trialWord);

         }
        tries++;//increment tries 
    }
    return tries; //return number of attempts needed for user to guess word correctly
}

int main(){
    int rounds; //number of rounds
    int score; //score for round
    double totalScore; //total score that can be converted into average
    int minScore; //minimum score
    int maxScore; //maximum score
    char secretWord[7]; //the secret word
    int wordnum = 0; //random integer we will use use as index to get our secret word

    cout << fixed<<setprecision(2); //setting precision of double digits after decimal point to 2
    
    char wordList[8000][7]; //spec wants at least 8000 C-strings. each c-string is at most 6 chars+ one null character= 7 characters
    const char WORDFILENAME[] = "/Users/vishal/Desktop/CS31/Project5/words.txt"; //path for word file
    int numWords = getWords(wordList, 10000, WORDFILENAME); //populate wordList with words from file. numWords is number of words in wordList
    if(numWords<1){ //if 0 words were loaded from the file, game does not run
        cout << "No words were loaded, so I can't play the game.";
        return 0;
    }

    cout << "How many rounds do you want to play? ";
    cin >> rounds;
    if(rounds<=0){
        cout << "The number of rounds must be positive.";
        return 0; //program ends
    }
    cin.ignore(1000, '\n'); //ignore additional input beyond integer for number of rounds to be played
    cout << endl;
   

    for(int i=1; i<=rounds; i++){
        wordnum = randInt(0, numWords-1); //we choose a random word in wordList out of the words loaded from the file
        strcpy(secretWord, wordList[wordnum]); //copy value of wordlist to a variable we can use
        cerr << "Secret word is: "<<secretWord << endl; //print statement to debug
        //cerr << "numWords is: "<<wordnum<<endl; //print statement to debug

        cout << "Round " <<i<<endl;
        cout<< "The secret word is " << strlen(secretWord) << " letters long."<<endl;
        // find the size of the secret word

        score+=runOneRound(wordList, numWords, wordnum);  //run a round and add attempts to score
        if(score<minScore || minScore==0){ //change minScore accordingly
            minScore=score;
        }
        if(score>maxScore || maxScore==0){ //change maxScore accordingly
            maxScore=score;
        }

        //outputting number of tries 
        if(score==1){
        cout << "You got it in 1 try."<<endl;
        }
        else{
            cout << "You got it in " <<score<<" tries."<<endl;
        }

        totalScore += score; //add score of this round to cumulative score
        cout << "Average: "<<totalScore/i<<", minimum: "<<minScore<<", maximum: "<<maxScore<<endl<<endl; //check if if the double endl is allowed
        // How text should be outputted: Average: 7.00, minimum: 7, maximum: 7

        score=0; //reset score variable
    }
}

