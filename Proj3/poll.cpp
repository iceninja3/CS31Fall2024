#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;


int stringtoint(string str, bool twodigit){ //this function converts a string input into integers
    int num=0; //this variable holds the number that is extracted from the string
    if (twodigit){ //if the number of votes has two digits
        num += (str.at(0)-'0')*10; //extracting tens place of votes number
        num += str.at(1)-'0'; //extracting ones place of votes number
    }
    else{ //if the number of votes has one digit
        num += str.at(0)-'0'; //extracting ones place of vote number
    }
    
    return num; //returns integer number of votes
} //We use this function later to modify the votecount variable


bool isValidUppercaseStateCode(string stateCode){ 
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NJ.NH.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
} //this is Professor Smallberg's provided code to verify if a state is real

bool hasRightSyntax(string pollData) {
    int strSize = pollData.size();
    string str = pollData; //using str as a substitute for pollData

    for (int i=0; i<strSize;i++) {
        str.at(i)=toupper(str.at(i)); //converts all characters to upper case, allowing us to later check if state codes are valid
        if (!isalnum(str.at(i))) {  // Only letters and digits are valid chars in this string
            return false;  // If non-alphanumeric char identified, string is invalid
        }
    }


    while (strSize>=4){  //4 is the smallest size of a state prediction. if strSize is less than four it is not valid
      if (!isalpha(str.at(0))){ //first character in a state prediction must be a letter
        return false;
      }

      if (!isdigit(str.at(1))){ //second char in a state prediction must be a number
        return false;
      }
      
      if (isdigit(str.at(2))){//we can tell if number of votes is two digits depending on if third char is a digit or not
        if (!(isalpha(str.at(3)) && isalpha(str.at(4)))){//if number of votes is two digits and two chars after the number are not letters
         return false;
        }
        if(!(isValidUppercaseStateCode(str.substr(3,2)))){ //checking if state code in state prediction is valid
          return false;
        }
        str = str.replace(0,5,""); //we have analyzed 5 chars in pollData. We now remove them from str and go on to analyzed the next substring
      }

      else if (isalpha(str.at(2))){ //if third char is a letter then number of votes is one digit
        if (!isalpha(str.at(3))){ //if two characters after 1 digit vote number aren't letters
          return false;
        }
        if(!(isValidUppercaseStateCode(str.substr(2,2)))){ //checking if state code is valid
          return false;
        }
        str = str.replace(0,4,""); //we've analyzed four chars. we now remove them and move on to analyzed the next substring 
      }
      
      strSize = str.size(); //updating value of strSize to capture the fact that characters were removed
    }
    
    if (strSize<4 &&strSize>0){ //if there are "leftover" characters after all party codes are eliminated from str then the poll data string is not valid
        return false;
    }

    return true; //return true by default (this ensures empty string returns as a valid pollData string)
}

int computeVotes(string pollData, char party, int& voteCount){
    
    if (!(hasRightSyntax(pollData))){ //if the pollData string's syntax is wrong computeVotes returns 1
        return 1;
    }

    int strSize = pollData.size(); //storing size of pollData string in a variable

    for (int i=1; i<strSize-1; i++){
        if (pollData.at(i)=='0'){ //identifies 0's in string
          if (!(isdigit(pollData.at(i-1)) || isdigit(pollData.at(i+1)))){ //if both charaters next to 0 aren't digits
            return 2; //if chars next to 0 are not digits that means 0 is the number of votes, which is invalid
          }
          if(pollData.at(i-1)=='0'){ //if there is a 0 next to 0 then vote number is 0 so the string is invalid
            return 2;
          }
        }
    }

    if (!(isalpha(party))){ //if the party character isn't an alphabetic letter the program returns 3
        return 3;
    }

    voteCount=0; //error handling is done. we now set voteCount to zero to accurately count votes

    //Now the actual changes to voteCount happen
    string str = pollData;

    while (strSize>=4){  //4 is least size of a valid state prediction
      if (toupper(str.at(0))==toupper(party)){ //if first char of str is same as the letter of the party we are counting votes for
        if (isdigit(str.at(2))){//if number of votes is two digits
          voteCount += stringtoint(str.substr(1,2), true); //we use our custom function to convert the substring into an integer
        }
        else{//if number of votes is one digit
          voteCount += stringtoint(str.substr(1,1), false); //custom function changes substring into integer
        }
    }

      if (isdigit(str.at(2))){ //if number of votes is two digits we remove five characters from the str string
          str = str.replace(0,5,"");
      }
      else{//if number of votes is one digit we remove four characters from the str string
        str = str.replace(0,4,"");
      }

      strSize = str.size(); //str has characters removed so it's size has changed
    }
    return 0; //countVotes is changed and no errors have been found in the data string so we simply return 0 as specified in the spec
}

int main(){
    int voteCount=9999;
    assert(computeVotes("R40TX", 'r', voteCount)==0 && voteCount==40);

    voteCount =0;
    assert(computeVotes("R40TX", 'r', voteCount)==0 && voteCount==40);
    
    /* string pollData="D00TX";
    char party='R';
    

    cout << "ComputeVotes returns: " << computeVotes(pollData, party, voteCount)<<endl;
    cout << "The syntax is: " << hasRightSyntax(pollData) << endl << "Votes: " << voteCount << endl;*/
    
}