/**
 *   @file: cc-balance.cc
 * @author: Easton Scowden
 *   @date: 10/17/2019
 *  @brief: A program that reads data about credit card holders, and returns a list or value. The list or value is dependent on what the user wants. 
 * The four options include -a which returns balances above a specified amount, -b which is the opposite, -d number of days they have left to pay or 
 * -A which returns an average. 
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <fstream>
using namespace std;

void customerInfo(int &id, string &firstName, string &lastName, 
                  double &bal, int &days, ifstream &instream) ; // gathers the customer info by 5 variables
bool isValidOption(string option) ; // checks if option user inputs is valid
void processBalance(string option, double balance,
                  ifstream &instream, ofstream &outstream) ; // works for two options checks the balance to see if it is below or above 
                                                            // a specific number inputted by the user
void processBalanceDue(int numDays, ifstream &instream, ofstream &outstream) ; // returns the customers which the days are within in the specified day inputted
void outputSummary(ifstream &instream, ofstream &outstream) ; // prints the average/total of all balances, and also all of the data in the file

int main(int argc, char const *argv[]) {
    ifstream inStream ; // instream and outstream for all the functions 
    ofstream outStream ; 
    if(argc == 4 || argc == 5){
        if(isValidOption(argv[1])){
            //checks the option inputted and then runs the function that corresponds with that option
            if(strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "-b") == 0){
                inStream.open(argv[3]) ;
                outStream.open(argv[4]) ;
                processBalance(argv[1], stod(argv[2]), inStream, outStream) ; 
                inStream.close() ; 
                outStream.close() ;
            }else if(strcmp(argv[1], "-d") == 0){
                inStream.open(argv[3]) ;
                outStream.open(argv[4]) ;
                processBalanceDue(stoi(argv[2]), inStream, outStream) ; 
                inStream.close() ; 
                outStream.close() ;
            }else if( strcmp(argv[1], "-A") == 0){
                inStream.open(argv[2]) ; 
                outStream.open(argv[3]) ; 
                outputSummary(inStream, outStream) ; 
                inStream.close() ;
                outStream.close() ; 
            }
        }  else {
            //returns invalid if the option is not one of the specified 
            cout << "Invalid option please try again." ; 
        }
    } else {
        cout << "Invalid amount of arguments please try again." ; 
    }
    return 0 ;
}

void customerInfo(int &id, string &firstName, string &lastName, double &bal, int &days, ifstream &instreamInfo){
    instreamInfo >> id >> firstName >> lastName >> bal >> days ; 
}

bool isValidOption(string option){
    if(option == "-a" || option == "-b" || option == "-d" || option == "-A"){
        return true ; 
    } else {
        return false ; 
    }
}

void processBalance(string option, double balance, ifstream &instream, ofstream &outstream) {
    //declares variables of all the customers information 
    int id ; 
    string firstName ; 
    string lastName ; 
    double bal ; 
    int days ; 

    if(option == "-a"){
        while(!instream.eof()){
            //declaring the customer info 
            customerInfo(id, firstName, lastName, bal, days, instream) ; 
            //since option is a, it checks if bal is aboved the specified balance
            if(bal >= balance){
                outstream << firstName << " " << lastName << "[" << id << "] " << "$" << bal << endl ; 
                outstream << " Days til due: " << days << endl ; 
            }
        }
    } else {
        while(!instream.eof()){
            customerInfo(id, firstName, lastName, bal, days, instream) ; 
            //option is b, so it checks if bal is below specified balance 
            if(bal <= balance){
                outstream << firstName << " " << lastName << "[" << id << "] " << "$" << bal << endl ; 
                outstream << " Days til due: " << days << endl ; 
            }
        }
    }
}

void processBalanceDue(int numDays, ifstream &instream, ofstream &outstream){
    int id ; 
    string firstName ; 
    string lastName ; 
    double bal ; 
    int days ;

    while(!instream.eof()){
        customerInfo(id, firstName, lastName, bal, days, instream) ; 
        if(days <= numDays && bal != 0){
            outstream << firstName << " " << lastName << "[" << id << "] " << "$" << bal << endl ; 
            outstream << " Days til due: " << days << endl ; 
        }
    }
}

void outputSummary(ifstream &instream, ofstream &outstream){
    int id ; 
    string firstName ; 
    string lastName ; 
    double bal ; 
    int days ;
    double totalBal ;
    double averageBal ; 
    int count = 0 ;

    while(!instream.eof()){
        customerInfo(id, firstName, lastName, bal, days, instream) ; 
        totalBal = totalBal + bal ; //finding the total balance
        outstream << firstName << " " << lastName << "[" << id << "] " <<  "$" << bal << endl  ; 
        outstream << setw(20) << " Days til due: " << days << endl ; 
        count += 1 ; 
    }
    // finding the average 
    averageBal = totalBal / count ; 
    outstream.setf(ios::fixed);
    outstream.setf(ios::showpoint);
    outstream.precision(2);
    outstream << endl << endl << "Total Balance: $" << totalBal << endl << "Average Balance: $" << averageBal << endl ; 
}