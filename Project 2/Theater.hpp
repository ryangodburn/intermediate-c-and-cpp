/* ===================================================================
 * Author: Ryan Godburn
 * Theater Class                            Theater.hpp / Theater.cpp
 * Created on 4/3/2023
 * Copyright: This is for educational purposes only.
 * All rights reserved, use with my express written permission only.
 * Description: object that functions as a ticketing system for a
 * specific screen at a theater
 * Written in C++, Ansi-style.
 * ===================================================================
 */

// safe class 
#pragma once

// libraries
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>

// easy read
using namespace std;

// Theater "model" class responsible for storing data about a screen
class Theater {

// Author: Ryan Godburn
// private data members of class Theater
private:
  int theaterNumber;
  string movieName;
  int seats;
  double ticketPrice;
  vector<string>dates;
  vector<vector<string>> showtimes;  
  vector<vector<int>> seatsLeft;

// Author: Ryan Godburn
// public functions
public:
  Theater() = default; // default constructor (empty object)
  Theater(int initNumber); 
  // construct Theater object with data
  bool isDate(string otherDate); // check dates
  string toString(int dateIndex); // string to print theater details
  // string to print showtime details   
  string toStringSpecific(int dateIndex, int timeIndex); 
  // string formatted ticket
  string toFile();  // string to print theater objects to output txt file
  void purchaseTicket(int dateIndex, int timeIndex, int numberSeatsPurchased); 
  // deals with changing variables to reflect purchase
  void listName(); // prints movie name
  void listDates(); // prints movie dates
  int getDateIndex(string inputDate); // match date with correct index value
  int totalTimes(); // return max date index value
  bool isFull(int dateIndex, int timeIndex); // returns if showing is full
  // returns if number of tickets can be purchased for showing
  bool canBuy(int dateIndex, int timeIndex, int numberTickets); 
  void printTotal(int numberTickets); // prints total of tickets purchased
  string getDate();// returns date For Final code
  bool isTestDate(string inputDate); // checks date at index 0 for Final code
  bool isStringNull(); // checks if name has NULL in it
};