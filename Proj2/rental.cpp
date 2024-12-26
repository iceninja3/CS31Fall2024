
//  main.cpp
//  CS31 Project 2
//
//  Created by Vishal Dandamudi on 10/11/24.


#include <iostream>
#include <string>
using namespace std;

   int main(){
       
       //initializing variables used in the program
       int initialOdom;
       int endOdom;
       int rentDays;
       string customerName;
       string luxuryCar;
       bool isLuxCar=false;
       int startingMonth;
       double rentalCharge=0;

       cout.setf(ios::fixed);
       cout.precision(2); 
       //Setting precision of numbers so that end has exactly two digits to right of decimal point
       
       
       //Getting input from user about rental information
       
       cout << "Odometer at start: ";
       cin >>initialOdom;
       if (initialOdom<0){ //Odometer's starting value should not be negative
           cout << "---\nThe starting odometer reading must not be negative.\n";
           return 0;
       }
       
       cout << "Odometer at end: "; //Odometer's ending value should not be less than starting value
       cin >>endOdom;
       if (endOdom<initialOdom){
           cout << "---\nThe ending odometer reading must be at least as large as the starting reading.\n";
           return 0;
       }
       
       cout << "Rental Days: "; //number of days rented should be more than 0
       cin >> rentDays;
       if (rentDays<=0){
           cout<< "---\nThe number of rental days must be positive.\n";
           return 0;
       }
       cin.ignore(10000, '\n'); //flushing the input buffer because cin leaves a \n in it
       
       cout << "Customer Name: ";
       getline(cin, customerName);
       if (customerName==""){ //empty string is not a valid customer name
           cout<< "---\nYou must enter a customer name.\n";
           return 0;
       }
       
    
       cout << "Luxury Car? (y/n): ";
       cin >> luxuryCar;
       if (luxuryCar=="y"){
           isLuxCar=true;
       }
       else if (luxuryCar=="n"){
           isLuxCar=false;
       }
       else{
           cout << "---\nYou must enter y or n.\n";
           return 0;
       }
       
       
       cout << "Starting month (1=Jan, 2=Feb, etc.): ";
       cin >> startingMonth;
       if (!(startingMonth>=1 && startingMonth<=12)){
           cout << "---\nThe month number must be in the range 1 through 12.\n";
           return 0;
       }
       
       
       cout << "---" <<endl;
      
      
       if (isLuxCar){
           rentalCharge += 75*rentDays;
       }
       else {
           rentalCharge += 45*rentDays;
       }
       //Calculating base charge
       
       int milesDriven = endOdom-initialOdom;
       
       
       
       if (milesDriven <= 100){
           rentalCharge += milesDriven*0.33;
       }
       else { //in case milesDriven is greater than 100 miles
           rentalCharge += 100*0.33;
           
           if (milesDriven<=600){
               if (startingMonth==12 || startingMonth==3|| startingMonth==2 || startingMonth==1){
                   rentalCharge += (milesDriven-100)*0.33;
               } //if rented in a winter month we charge 0.33
               else{
                   rentalCharge += (milesDriven-100)*0.27;
               }
           }
           
           
           else {
               if (startingMonth==12 || startingMonth==3|| startingMonth==2 || startingMonth==1){
                   rentalCharge += (500)*0.33;
               } //if rented in a winter month we charge 0.33
               else{
                   rentalCharge += (500)*0.27;
               }
               
               rentalCharge += (milesDriven-600)*0.21;
           } //for every mile beyond 600 miles we charge $0.21
       }
       
       
       
       
       
       cout << "The rental charge for "<<customerName<< " is $" << rentalCharge <<endl;
       return 0;
       
   }
// why is it restarting when we're done?
//



/* User input:
 Your program must accept as input the odometer readings at the start and end of the rental, the number of days the car was rented, the customer's name, whether or not the car is a luxury car, and the month the rental started.

 Here is an example of a dialog with the program (user input is shown here in boldface):

     Odometer at start: 2417
     Odometer at end: 2754
     Rental days: 4
     Customer name: Mario Andretti
     Luxury car? (y/n): n
     Starting month (1=Jan, 2=Feb, etc.): 10
     ---
     The rental charge for Mario Andretti is $276.99
 */


/* Errors that your program should be wary of:
 If the starting odometer reading is negative:
    The starting odometer reading must not be negative.
 If the ending odometer reading is less than the starting reading:
    The ending odometer reading must be at least as large as the starting reading.
 If the number of rental days is not positive:
    The number of rental days must be positive.
 If an empty string was provided for the customer name:
    You must enter a customer name.
 If the luxury status is not y or n (must be lower case):
    You must enter y or n.
 If the month number is not an integer between 1 and 12 inclusive:
    The month number must be in the range 1 through 12.
 If the input is valid and none of the preceding situations holds:
    The rental charge for customer is $amount

 */


