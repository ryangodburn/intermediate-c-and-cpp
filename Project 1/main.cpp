/* ===================================================================
 * Author: Ryan Godburn, Ayesha Abbassi, and Jason Nguyen
 * Movie Ticketing System                                  main.cpp
 * Dependencies: Theater.hpp && Theater.cpp
 * Created on 4/3/2023
 * Copyright: This is for educational purposes only.
 * All rights reserved, use with my express written permission only.
 * Description: Functioning ticketing system for a movie theater
 * Written in C++, Ansi-style.
 * ===================================================================
 */

// libraries
#include "Theater.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

// easy read
using namespace std;

// ============================================================================
// main();
// Acts as purchasing program for tickets for a movie theater with 10 screens
// ============================================================================
int main() {

  // create variables
  int movieListIndex = 0;
  int selectedMovie = 0;
  string selectedDate;
  int dateIndex;
  int selectedTime = 0;
  int purchaseAmount = 0;

  // create vector for movie theater
  vector<Theater> movieTheater;
  // initialize 10 screens inside movie theater
  movieTheater.push_back(Theater(1));
  movieTheater.push_back(Theater(2));
  movieTheater.push_back(Theater(3));
  movieTheater.push_back(Theater(4));
  movieTheater.push_back(Theater(5));
  movieTheater.push_back(Theater(6));
  movieTheater.push_back(Theater(7));
  movieTheater.push_back(Theater(8));
  movieTheater.push_back(Theater(9));
  movieTheater.push_back(Theater(10));

  // present movie options
  cout << endl
       << "Movie Ticketing System" << endl
       << endl
       << "Choose Movie:" << endl;
  for (Theater &theater : movieTheater) {
    cout << movieListIndex + 1 << " - ";
    theater.listName();
    cout << endl;
    movieListIndex++;
  }
  // select movie with error checking
  for (;;) {
    cin >> selectedMovie;
    if (selectedMovie <= movieListIndex && selectedMovie >= 1) {
      break;
    }
    // ignore bad input & error output
    // https://www.cs.uleth.ca/~bomhof/lect/Malik_03_07.pdf
    cin.clear();
    cin.ignore();
    cout << endl << "Please choose a valid number" << endl;
  }
  // user input -> index number
  selectedMovie--;

  // list movie dates
  cout << endl << "Type Available Date:" << endl;
  movieTheater[selectedMovie].listDates();
  cout << endl;
  // input for dates with error checking
  for (;;) {
    cin >> selectedDate;
    if (movieTheater[selectedMovie].isDate(selectedDate)) {
      break;
    }
    // ignore bad input & error output
    cin.clear();
    cin.ignore();
    cout << endl << "Please type a valid date" << endl;
  }
  // retrive date index number from string
  dateIndex = movieTheater[selectedMovie].getDateIndex(selectedDate);

  // list movie times for date
  cout << endl << movieTheater[selectedMovie].toString(dateIndex) << endl;
  // input for movie time with error checking
  for (;;) {
    cin >> selectedTime;
    if ((selectedTime >= 1 &&
         selectedTime <= movieTheater[selectedMovie].totalTimes() - 1) &&
        !movieTheater[selectedMovie].isFull(dateIndex, selectedTime - 1)) {
      break;
    }
    // ignore bad input & error output
    cin.clear();
    cin.ignore();
    if (selectedTime <= 0) {
      cout << endl << "Please choose a valid showtime number" << endl;
    } else if (movieTheater[selectedMovie].isFull(dateIndex,
                                                  selectedTime - 1)) {
      cout << endl
           << "This showtime is full. Please choose another time" << endl;
    } else {
      cout << endl << "Please choose a valid showtime number" << endl;
    }
  }
  // user time -> index number
  selectedTime--;

  // present showtime information and purchase prompt
  cout << endl
       << "How many tickets would you like to purchase?" << endl
       << movieTheater[selectedMovie].toStringSpecific(dateIndex, selectedTime)
       << endl;
  for (;;) {
    cin >> purchaseAmount;
    if (movieTheater[selectedMovie].canBuy(dateIndex, selectedTime,
                                           purchaseAmount)) {
      break;
    }
    // ignore bad input & error output
    cin.clear();
    cin.ignore();
    cout << endl << "You cannot buy that many tickets" << endl;
  }
  // perform operations to purchase ticket and subtract remaining seats, print
  // and display total cost
  movieTheater[selectedMovie].purchaseTicket(dateIndex, selectedTime,
                                             purchaseAmount);
  movieTheater[selectedMovie].printTotal(purchaseAmount);
  for (Theater &theater : movieTheater) {
    theater.writeFile(theater.toFile());
  }

  // end message
  cout << endl << "Thank you for using this program!" << endl;
  return 0;
}