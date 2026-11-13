# Intermediate C and C++

Coursework from **Intermediate C and C++** at the **University of New Haven**, Spring 2023 (first year, spring semester).

- **Author:** Ryan Godburn
- **Team (main program):** Ryan Godburn, Ayesha Abbassi, Jason Nguyen
- **Language:** C++

## Movie Ticketing System

A console ticketing system for a ten-screen movie theater, built in two stages. The `Theater` class (written by Ryan Godburn) represents one screen: it loads its movie, price, seat count, show dates, showtimes and remaining seats from `data.txt` and sells tickets. After a purchase, the program writes the updated seat counts to `ouput.txt`.

### Project 1

- Loads ten movies from `data.txt` and walks the user through choosing a movie, a date, a showtime and a number of tickets.
- Validates every input: numbers out of range, dates that aren't offered, letters or symbols instead of numbers, and buying zero tickets or more than the seats left.
- Prints the order total and appends the updated seat counts to `ouput.txt`.

### Project 2

- Adds an eleventh movie (*Guardians of the Galaxy 3*).
- Adds a hash table keyed on each movie's first show date. Ryan Godburn wrote the date hash function (`hashIt`); Jason Nguyen and Ayesha Abbassi wrote the code that fills the table and, after a movie is chosen, lists every show that opens on the same date.
- If `data.txt` is missing, the program keeps running with "Null" placeholder data instead of exiting.

## Files

Each project folder has the same layout:

| File | Purpose |
| --- | --- |
| `main.cpp` | Controller program: menus, input validation, purchase flow |
| `Theater.hpp` / `Theater.cpp` | `Theater` class, one object per screen |
| `data.txt` | Input data: movies, prices, dates, showtimes and seats per showing |
| `ouput.txt` | Sample output after a purchase (the program writes to this exact file name) |
| `testplan.txt` | Test cases with console transcripts, including the error cases |
| `description.txt` | The header comments used for the source files |

## Build and run

Run the program from inside a project folder so it can find `data.txt`:

```bash
cd "Project 1"            # or "Project 2"
g++ -std=c++17 -o theater main.cpp Theater.cpp
./theater
```

---

*Archived coursework, shared as part of my portfolio. If you're taking this course now, please follow your instructor's academic integrity policy.*
