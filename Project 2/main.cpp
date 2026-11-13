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

// defines
#define rows 97

// easy read
using namespace std;

// function protoypes
int hashIt(string targetDate);
void writeFile(string text);

// movie theather part - Ryan Godburn
// hash table part - Jason Nguyen and Ayesha Abbassi
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

  // Part 1 - Ryan Godburn
  // create vector for movie theater
  vector<Theater> hashTable[rows];
  // initialize 10 screens inside movie theater
  hashTable[0].push_back(Theater(1));
  hashTable[1].push_back(Theater(2));
  hashTable[2].push_back(Theater(3));
  hashTable[3].push_back(Theater(4));
  hashTable[4].push_back(Theater(5));
  hashTable[5].push_back(Theater(6));
  hashTable[6].push_back(Theater(7));
  hashTable[7].push_back(Theater(8));
  hashTable[8].push_back(Theater(9));
  hashTable[9].push_back(Theater(10));

  // Create test hashTable
  vector<Theater>
      hashTable1[rows]; // No idea why program doesnt compile without this line
                        // and causes a segmentation fault at the end???? Its
                        // not refrenced anywhere.

  //===============
  // Part 2 - Jason Nguyen and Ayesha Abbassi
  //===============
  // Puts each object in respective hashIt indexes of vector for part 2
  for (int i = 0; i < 10; i++) {
    hashTable[hashIt(hashTable[i][0].getDate())].push_back(Theater(i + 1));
  }

  //===============
  // Part 3 - Jason Nguyen and Ayesha Abbassi
  //===============
  // adds new object to hashTable vector based on date at the index calculated
  // by hashIt()
  hashTable[10].push_back(Theater(11));
  int hashSpecificIndex = hashIt(hashTable[10][0].getDate());
  hashTable[hashSpecificIndex].push_back(hashTable[10][0]);

  // present movie options
  cout << endl
       << "Movie Ticketing System" << endl
       << endl
       << "Choose Movie:" << endl;
  for (int i = 0; i < 11; i++) {
    Theater &theater = hashTable[i][0];
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
  Theater &theater = hashTable[selectedMovie][0];
  

    //===============
    // Part 4 - Jason Nguyen and Ayesha Abbassi
    //===============
    // uses hash Table and checks the index of the hashIt of the first date
    // the movie is shown and prints all objects that match for part 4
  cout << endl << "Shows with matching hash table index:" << endl;
  if (!theater.isStringNull()) {
    string dateTest = hashTable[selectedMovie][0].getDate();
    int index1 = hashIt(
        dateTest); // Set index1 to index of the hash of the selected date
    for (int i = 0; i < hashTable[index1].size();
         i++) { // Grabs loops through entire vector
      if (hashTable[index1][i].getDate() ==
          dateTest) { // Tests if dates match the selected date
        cout << hashTable[index1][i]
                    .toFile(); // Prints objects with matching dates to console
      } else {
        cout << "None"; // Returns this if date is not found in any movies in
                        // vector
      }
    }
  }

  // list movie dates
  cout << endl << "Type Available Date:" << endl;
  theater.listDates();
  cout << endl;
  // input for dates with error checking
  for (;;) {
    cin >> selectedDate;
    if (theater.isDate(selectedDate)) {
      break;
    }
    // ignore bad input & error output
    cin.clear();
    cin.ignore();
    cout << endl << "Please type a valid date" << endl;
  }
  // retrive date index number from string
  dateIndex = theater.getDateIndex(selectedDate);

  // list movie times for date
  cout << endl << theater.toString(dateIndex) << endl;
  // input for movie time with error checking
  for (;;) {
    cin >> selectedTime;
    if ((selectedTime >= 1 && selectedTime <= theater.totalTimes() - 1) &&
        !theater.isFull(dateIndex, selectedTime - 1)) {
      break;
    }
    // ignore bad input & error output
    cin.clear();
    cin.ignore();
    if (selectedTime <= 0) {
      cout << endl << "Please choose a valid showtime number" << endl;
    } else if (theater.isFull(dateIndex, selectedTime - 1)) {
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
       << theater.toStringSpecific(dateIndex, selectedTime) << endl;
  for (;;) {
    cin >> purchaseAmount;
    if (theater.canBuy(dateIndex, selectedTime, purchaseAmount)) {
      break;
    }
    // ignore bad input & error output
    cin.clear();
    cin.ignore();
    cout << endl << "You cannot buy that many tickets" << endl;
  }
  // perform operations to purchase ticket and subtract remaining seats, print
  // and display total cost
  theater.purchaseTicket(dateIndex, selectedTime, purchaseAmount);
  theater.printTotal(purchaseAmount);

  // Part 6 - Ryan Godburn
  // Writes the hashTable vector into the output.txt file
  for (int i = 0; i < 11; i++) {
    Theater &theater = hashTable[i][0];
    writeFile(theater.toFile());
  }

  // end message
  cout << endl << "Thank you for using this program!" << endl;
  return 0;
}

// Part 5
// ============================================================================
// Author: Ryan Godburn
// Takes a date in string as the argument and returns a random-looking integer
// to use as index for the hash table
// ============================================================================
int hashIt(string targetDate) {
  // create variables for parts of dates
  string monthNames[] = {"January",   "February", "March",    "April",
                         "May",       "June",     "July",     "August",
                         "September", "October",  "November", "December"};
  int year = stoi(targetDate.substr(6, 4));
  int day = stoi(targetDate.substr(3, 2));
  int month = stoi(targetDate.substr(0, 2));
  string nameOfMonth = monthNames[month - 1];
  // create other variables
  int index;
  //  Create a long integer named key and initialize it to the year squared plus
  //  day.
  long key = (year * year) + day;
  // Also create a temp variable of the same type initialized to zero.
  long temp = 0;

  // Repeat loop until used all the letters from the month (going backward from
  // the last letter to the first letter).
  for (int a = nameOfMonth.length() - 1; a >= 0; a--) {
    // Use a mask to get the 5 high-order bits of key (5 leftmost bits) and save
    // them into the temp variable.
    temp = (key & 0xF8000000);
    // . Shift these bits to the five low order bits (5 rightmost bits) of the
    // temp variable.
    temp = temp >> 27;
    // Shift the key’s 5 bits toward the left. This will drop those bits off the
    // end and make the 5 low order bits all zero.
    key = key << 5;
    // Use bitwise OR of temp with key to put the 5 bits that you saved in the
    // temp variable back into the key in the low order 5 bits.
    key = key | temp;
    // Get the name of the month from the date and save it in a string. Then
    // cast the last letter of the month to an int and xor (^) it with key and
    // save it as the key
    key = key ^ (int)nameOfMonth[a];
  }

  // Calculate index = key % the length of your array of vectors (prime number
  // you chose as the number of rows).
  index = key % 97;

  // return index
  return index;
}

// ============================================================================
// Author: Ryan Godburn
// Writes a provided string (will be from toFile) to write (output) to
// output.txt
// ============================================================================
void writeFile(string text) {
  // opens file stream in append mode and checks file
  // https://cplusplus.com/doc/oldtutorial/files/
  ofstream outputFile("ouput.txt", ios::app);
  if (!outputFile.is_open()) {
    cout << "Unable to open file" << endl;
  }
  // writes to file
  outputFile << text;
  // closes
  outputFile.close();
}