#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int appendToAll(string a[], int n, string value){ //done1  
    if (n<0){
        return -1;
    }
    for (int i=0; i<n; i++){
        a[i]=a[i]+value;
    }
    return n;
}
/* Append value to the end of each of the n elements of the array and return n. [Of course, in this and other functions, if n is negative, the paragraph above that starts "Notwithstanding" trumps this by requiring that the function return −1. Also, in the description of this function and the others, when we say "the array", we mean the n elements that the function is told to consider to be part of the array.] For example:
string candidate[5] = { "donald", "kamala", "jd", "tim", "jill" };
int j = appendToAll(candidate, 5, "!!!");  // returns 5
    // now candi date[0] is "donald!!!", candidate[1] is "kamala!!!", ...,
    // and candidate[4] is "jill!!!" */

int lookup(const string a[], int n, string target){ //done1
    if (n<0){
        return -1;
    }

    for (int i=0; i<n; i++){
        if(a[i]==target){
           return i;
        }
    }
    return -1;
}
/* Return the position of a string in the array that is equal to target; if there is more than one such 
string, return the smallest position number of such a matching string. Return −1 if there is no such string.
 As noted above, case matters: Do not consider "JOe" to be equal to "jOE". */

int positionOfMax(const string a[], int n){ //done1
    if (n<=0){
        return -1;
    }

    int posMax=0; 
    for(int i=1; i<n; i++){
        if(a[i]>a[posMax]){ //spec wants greatest string with least index
            posMax=i;
        }
    }
    return posMax;
}
// Return the position of a string in the array such that that string is >= every string in the array. 
// If there is more than one such string, return the smallest position number of such a string. 
// Return −1 if the function should consider no elements to be part of the array. For example:

int rotateLeft(string a[], int n, int pos){ //done1
    if (n<0 || pos>=n || pos<0){
        return -1;
    }
    string tempVal = a[pos];
    for(int i=pos; i<n; i++){
      a[i]=a[i+1];
    }
    a[n-1]=tempVal;
    return pos;
}
//Make sure to test if n is less than the actual size of the array for every function

// Eliminate the item at position pos by copying all elements after it one place to the left. 
// Put the item that was thus eliminated into the last position of the array that the function knows about. 
// Return the original position of the item that was moved to the end.

int countRuns(const string a[], int n){ //done1
    if (n<0){
        return -1;
    }
    if(n==0){
        return 0;
    }

    int count=0;
    for(int i=0; i<n-1; i++){
        if(a[i]!=a[i+1]){
            count++;
        }
    }

    return count+1; //we +1 because in the for loop we counted num of diffs
}

int flip(string a[], int n){ //done1
    if (n<0){
        return -1;
    }

    string tempVal;
    for(int i=0; i<n/2; i++){
        tempVal=a[i];
        a[i]=a[n-1-i];
        a[n-1-i]=tempVal;
    }

    return n;
} //check edge case of middle not changing

int differ(const string a1[], int n1, const string a2[], int n2){//done1
    if (n1<0 || n2<0){
        return -1;
    }

    if(n1<n2){
       for(int i=0; i<n1; i++){
        if(a1[i]!=a2[i]){
          return i;
          }
        }
       return n1;
    }
    else {
      for(int i=0; i<n2; i++){
        if(a1[i]!=a2[i]){
            return i;
            }
        }
        return n2;
    }
}

int subsequence(const string a1[], int n1, const string a2[], int n2){//done1
    if (n1<0 || n2<0){
        return -1;
    }

    if (n2==0){
        return 0; //if the subsequence to be found is the empty string then return the starting index
    }

    for(int i=0; i<n1; i++){ //for all indices in a1
        if(a1[i]==a2[0]){ //if a1[i] is same as starting index in a2
          for(int j=0; j<n2; j++){ //for all indices in a2
            if(i+j<n1){
                if(a1[i+j]!=a2[j]){
              break;
            }
            if(j==n2-1){
                return i;
            }

            }
            
          }
        }
        continue;
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2){//done1
    if (n1<0 || n2<0){
        return -1;
    }
    
    for (int i=0; i<n1; i++){
        for (int j=0; j<n2; j++){
            if(a1[i]==a2[j]){
                return i;
            }
        }
    }
    return -1;
}

int separate(string a[], int n, string separator){ //done1
   if (n<0){
        return -1;
    }
    
   string tempVal = "";
   int count=1; //initialized to non-zero value so while loop runs at least once
   while (count>0){ //while any changes were made
    count=0;
    for (int i=1; i<n; i++){
        if(a[i-1]>a[i]){ //if a[i-1] is greater than a[i] swap values
            tempVal = a[i-1];
            a[i-1]=a[i];
            a[i]=tempVal;
            count++;
        }
     }
   }
   for(int i=0; i<n; i++){
    if(a[i]>=separator){
        return i;
    }
   }
   return n;
}


int main(){ 
    //positionOfMaxTests
    // string people[6] = { "doug", "kamala", "melania", "9usha", "gwen", "6donald" };
    // int k = positionOfMax(people, 6); // returns 3, since  usha  is latest in alphabetic order
    // cout << k;
    
    //separate() tests
    // string people[6] = { "doug", "kamala", "melania", "usha", "gwen", "donald" };
    // int x = separate(people, 6, "joe");  //  returns 3
	// // people must now be
	// //      "doug"  "gwen"  "donald"  "kamala"  "usha"  "melania"
	// // or   "gwen"  "donald"  "doug"  "melania"  "kamala"  "usha"
	// // or one of several other orderings.
	// // All elements < "joe" (i.e., "gwen", "donald", and "doug")
	// //   come before all others
	// // All elements > "joe" (i.e., "usha", "kamala", and "melania")
	// //   come after all others
    // string people2[4] = { "jill", "tim", "jd", "joe" };
    // int y = separate(people2, 4, "joe");  //  returns 2
    // cout << x << " " <<y<<endl;
	// // people2 must now be either
	// //      "jd"  "jill"  "joe"  "tim"
	// // or   "jill"  "jd"  "joe"  "tim"
	// // All elements < "joe" (i.e., "jd" and "jill") come before all others.
	// // All elements > "joe" (i.e., "tim") come after all others.

    // for (int i=0; i<6; i++){
    //     cout <<people[i]<<endl; //should return array arranged well
    // } 
    // for (int i=0; i<4; i++){
    //     cout <<people2[i]<<endl; //should return array arranged well
    // } 


    // string a[4] = {"hi", "hi5", "hi3", "hi2"};
    // cout << separate(a, 4, "hi4")<<endl; //should return 3
    // for (int i=0; i<4; i++){
    //     cout <<a[i]<<endl; //should return array arranged well
    // } 

    // string a = "hi";
    // string b = "hi6";
    // if (a<b){
    //     cout << "we did it bois";
    // }


    
    //lookupany() test
    // string names[10] = { "kamala", "tim", "usha", "gwen", "donald", "jd" };
    // string set1[10] = { "donald", "melania", "gwen", "tim" };
    // int v = lookupAny(names, 6, set1, 4);  // returns 1 (a1 has "tim" there)
    // string set2[10] = { "jill", "joe" };
    // int w = lookupAny(names, 6, set2, 2);  // returns -1 (a1 has none)
    // cout << v <<" and " <<w<<endl;

    // subsequence test (test this one A LOT)
    // string names[10] = { "kamala", "tim", "usha", "gwen", "donald", "jd" };

    // string names1[10] = { "tim", "usha", "gwen" };
    // int t = subsequence(names, 6, names1, 3);  // returns 1

    // string names2[10] = { "kamala", "gwen" };
    // int u = subsequence(names, 5, names2, 2);  // returns -1 

    // string names3[10]={};
    // int q = subsequence(names, 6, names3, 0);
    // cout << t <<" "<<u<< " "<<q<<endl;

    
    //differ() test
    // string folks[6] = { "kamala", "doug", "", "jill", "jd", "donald" };
    // string group[5] = { "kamala", "doug", "donald", "", "jd" };
    // int r = differ(folks, 6, group, 5);
    // int s = differ(folks, 2, group, 1);
    // cout << r <<" "<<s<< endl;
    
    
    //flip() test
    // string folks[6] = { "kamala", "doug", "", "jill", "jd", "donald" };
    // int q = flip(folks, 4);  // returns 4
    // cout <<q<<endl;
    // for (int i=0; i<6;i++){
    //     cout<<folks[i]<<", ";
    // }
    // folks now contains:  "jill"  ""  "doug"  "kamala"  "jd"  "donald"


    //countRuns() test
    // string d[9] = { "melania", "doug", "gwen", "gwen", "jill", "jill", "jill", "gwen", "gwen"};
    // int p = countRuns(d, 9);  //  returns 5
    // cout << p; 

    
    //rotateLeft() test
    // string politician[5] = { "kamala", "donald", "jd", "tim", "joe" };
    // int m = rotateLeft(politician, 5, 3);  // returns 1
    // // politician now contains:  "kamala", "jd", "tim", "joe", "donald"
    // cout<<m<<endl;
    // for(int i=0; i<5; i++){
    //     cout << politician[i] << ", ";
    // } 


    //lookup tests
    // string arr[3] = {"1", "2", "A"};
    // cout << lookup(arr, 3, "a");


    //appendtoall() tests
    // string arr[3] = {"1", "2", "3"};
    // //cout << appendToAll(arr, 3, "!");
    // cout << appendToAll(arr, 0, "!")<<endl;
    // for(int i=0; i<3; i++){
    //     cout << arr[i] <<endl;
    // }
     string h[7] = { "melania", "kamala", "donald", "tim", "", "doug", "jd" };
	    assert(lookup(h, 7, "doug") == 5);
	    assert(lookup(h, 7, "donald") == 2);
	    assert(lookup(h, 2, "donald") == -1);
	    assert(positionOfMax(h, 7) == 3);

	    string g[4] = { "melania", "kamala", "jd", "usha" };
	    assert(differ(h, 4, g, 4) == 2);
	    assert(appendToAll(g, 4, "?") == 4 && g[0] == "melania?" && g[3] == "usha?");
	    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jd?" && g[3] == "kamala?");

	    string e[4] = { "donald", "tim", "", "doug" };
	    assert(subsequence(h, 7, e, 4) == 2);

	    string d[5] = { "kamala", "kamala", "kamala", "tim", "tim" };
	    assert(countRuns(d, 5) == 2);
	
	    string f[3] = { "jd", "donald", "gwen" };
	    assert(lookupAny(h, 7, f, 3) == 2);
	    assert(flip(f, 3) == 3 && f[0] == "gwen" && f[2] == "jd");
	
	    assert(separate(h, 7, "jd") == 3);
	
	    cout << "All tests succeeded" << endl;

    return 0;
}