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

// libraries
#include "Theater.hpp"

// ============================================================================
// Author: Ryan Godburn
// Constructor initializes Theater object with number, movie, total seats,
// ticket price, dates, and times
// ============================================================================
Theater::Theater(int initNumber) {
  // create variables
  theaterNumber = initNumber;
  string line;
  vector<string> times;
  // open file stream with error checking
  ifstream inputFile("data.txt");
  if (!inputFile.is_open()) {
    // continue with null information
    movieName = "Null";
    seats = 22;
    ticketPrice = 1.11;
    dates.push_back({"01/01/01"});
    dates.push_back({"01/10/01"});
    showtimes.push_back({"01:00", "10:00"});
    showtimes.push_back({"01:00", "10:00"});
    seatsLeft.push_back({2, 2});
    seatsLeft.push_back({2, 2});
    return;
  } 
    // read from data.txt
    // https://cplusplus.com/reference/string/string/rfind/
    // https://cplusplus.com/reference/string/string/getline/
    // https://cplusplus.com/reference/string/string/substr/
    // https://cplusplus.com/reference/sstream/stringstream/stringstream/
    // https://cplusplus.com/reference/string/stoi/
    // https://cplusplus.com/reference/string/stod/
    // https://cplusplus.com/reference/string/string/find_first_not_of/
    // read each line of data.txt
    while (getline(inputFile, line)) {
      // if it finds matching theater number
      if (line.rfind("Number: " + to_string(theaterNumber), 0) == 0) {
        // get next line
        getline(inputFile, line);
        // sets movie name
        movieName = line.substr(line.find(":") + 2);
        // gets next line
        getline(inputFile, line);
        // sets total seats
        seats = stoi(line.substr(line.find(":") + 2));
        // gets next line
        getline(inputFile, line);
        // sets ticket price
        ticketPrice = stod(line.substr(line.find(":") + 2));
        // gets next line
        getline(inputFile, line);
        // retrives dates vector items
        stringstream ss(line.substr(line.find(":") + 2));
        string date;
        while (getline(ss, date, ',')) {
          dates.push_back(date.substr(date.find_first_not_of(' ')));
        }
        // gets next line
        getline(inputFile, line);
        // retrives vector of vector for seats left
        stringstream ss2(line);
        string time;
        while (getline(ss2, time, ',')) {
          times.push_back(time.substr(time.find_first_not_of(' ')));
        }
        // stops when next line is empty
        while (getline(inputFile, line) && !line.empty()) {
          stringstream ss3(line);
          string seat;
          vector<int> row;
          while (getline(ss3, seat, ' ')) {
            row.push_back(stoi(seat));
          }
          seatsLeft.push_back(row);
        }
        // end loop
        break;
      }
    }

    // fills out dates vector
    for (int i = 0; i < dates.size(); i++) {
      showtimes.push_back(times);
    }
}

// ============================================================================
// Author: Ryan Godburn
// Compares if a provided string for a date in mm/dd/yyyy format matches with
// any of the dates of the movie playing
// ============================================================================
bool Theater::isDate(string otherDate) {
  // for each loop for each showing date
  for (string date : dates) {
    if (date == otherDate) {
      return true;
    }
  }
  return false;
}

// ============================================================================
// Author: Ryan Godburn
// Formats a string to show a movie's details including name, theater number,
// and times
// ============================================================================
string Theater::toString(int dateIndex) {
  // create variables
  int b = 0;
  // basic details
  string dayDetails = "Movie: " + movieName + "\nDate: " + dates[dateIndex] +
                      "\nTheater: " + to_string(theaterNumber) +
                      "\nEnter Number for Time:\n";
  // showtime details
  for (int a = 0; a < showtimes[dateIndex].size(); a++) {
    b++;
    dayDetails =
        dayDetails + to_string(a + 1) + "-" + showtimes[dateIndex][a] + " ";
    if (b == 5) {
      b = 0;
      dayDetails = dayDetails + "\n";
    }
  }
  // return final string
  return dayDetails;
}

// ============================================================================
// Author: Ryan Godburn
// Formats a string for a specific time a movie is playing including total
// seats, seats remaining, and price.
// ============================================================================
string Theater::toStringSpecific(int dateIndex, int timeIndex) {
  stringstream ss;
  ss << fixed << setprecision(2) << ticketPrice;
  string showcaseDetails =
      "Price: " + ss.str() + "\nTotal Seats: " + to_string(seats) +
      "\nSeats Remaining: " + to_string(seatsLeft[dateIndex][timeIndex]);
  return showcaseDetails;
}

// ============================================================================
// Author: Ryan Godburn
// Reduces remaining seats after ticket purchase
// ============================================================================
void Theater::purchaseTicket(int dateIndex, int timeIndex,
                             int numberSeatsPurchased) {
  seatsLeft[dateIndex][timeIndex] =
      seatsLeft[dateIndex][timeIndex] - numberSeatsPurchased;
}

// ============================================================================
// Author: Ryan Godburn
// Formats a string containing all details for the object
// ============================================================================
string Theater::toFile() {
  // for price printing
  stringstream stream;
  stream << fixed << setprecision(2) << ticketPrice;
  string price = stream.str();
  // basic details
  string details = "Number: " + to_string(theaterNumber) +
                   "\nShow: " + movieName + "\nSeats: " + to_string(seats) +
                   "\nPrice: " + price + "\n ";
  // dates details
  for (int i = 0; i < dates.size(); i++) {
    if (i == 0) {
      details += dates[i];
    } else {
      details += "," + dates[i];
    }
  }
  // times details
  details += "\n ";
  for (int i = 0; i < showtimes[0].size(); i++) {
    if (i == 0) {
      details += showtimes[0][i];
    } else {
      details += "," + showtimes[0][i];
    }
  }
  // seats left details
  details += "\n";
  for (vector<int> row : seatsLeft) {
    for (int seat : row) {
      details += to_string(seat) + " ";
    }
    details += "\n";
  }
  details += "\n";
  // return final string
  return details;
}

// ============================================================================
// Author: Ryan Godburn
//  prints the name of movie
// ============================================================================
void Theater::listName() { cout << movieName; }

// ============================================================================
// Author: Ryan Godburn
//  prints the dates of movie
// ============================================================================
void Theater::listDates() {
  string listOfDates;
  int b = 0;
  for (int a = 0; a < dates.size(); a++) {
    b++;
    listOfDates = listOfDates + dates[a] + " ";
    if (b == 4) {
      b = 0;
      listOfDates = listOfDates + "\n";
    }
  }
  cout << listOfDates;
}

// ============================================================================
// Author: Ryan Godburn
//  matches date input with int index of date for movie
// ============================================================================
int Theater::getDateIndex(string inputDate) {
  for (int a = 0; a < dates.size(); a++) {
    if (dates[a] == inputDate) {
      return a;
    }
  }
  return -1;
}

// ============================================================================
// Author: Ryan Godburn
//  returns max date index value
// ============================================================================
int Theater::totalTimes() { return dates.size(); }

// ============================================================================
// Author: Ryan Godburn
//  returns if showing is full or not
// ============================================================================
bool Theater::isFull(int dateIndex, int timeIndex) {
  if (seatsLeft[dateIndex][timeIndex] == 0) {
    return true;
  } else {
    return false;
  }
}

// ============================================================================
// Author: Ryan Godburn
//  returns if number of tickets can be purchased
// ============================================================================
bool Theater::canBuy(int dateIndex, int timeIndex, int numberTickets) {
  if (seatsLeft[dateIndex][timeIndex] >= numberTickets && numberTickets > 0) {
    return true;
  } else {
    return false;
  }
}

// ============================================================================
// Author: Ryan Godburn
//  prints total of tickets purchased
// ============================================================================
void Theater::printTotal(int numberTickets) {
  cout << fixed << setprecision(2) << "Total: $"
       << (numberTickets * ticketPrice) << endl;
}

// ============================================================================
// Author: Jason Nguyen
// returns the date used for final code
// ============================================================================
string Theater::getDate() { return dates[0]; }

// ============================================================================
// Author: Jason Nguyen
// returns a boolean if if date matches
// ============================================================================
// does not seem to compile with this so called directly in IF statement in main
bool Theater::isTestDate(string inputDate) {
  if (dates[0] == inputDate) {
    return true;
  } else {
    return false;
  }
}

// ============================================================================
// Author: Ryan Godburn
// checks if name is Null
// ============================================================================
bool Theater::isStringNull() {
  if (movieName == "Null") {
    return true;
  } else {
    return false;
  }
}