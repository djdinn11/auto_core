/*!
\file star.cc
\brief Implementation of journaling document creation and titling.

This file implements the functions declared in star.h, providing mechanisms
for creating journaling documents, generating episode titles, and managing
episode numbers through a database. It includes database interaction,
file saving routines, and title generation based on episode numbers.

Dependencies:
- SQLite3: Used for database interactions to manage episode numbers.
- main.h: Contains utility functions including print_to_screen() used for output.
*/

#include <star.h>
#include <clock.h>
#include <sqlite3.h>
#include <main.h>

/*!
* \brief Saves the current document.
*
* This function simulates the press of 'Ctrl+S' to save the current document.
* It uses the Windows SendInput function to send keyboard input to the active window.
*/
void save_file() {
    INPUT inputs[4] ={};
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL;
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 'S';
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = 'S';
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_CONTROL;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}

/*!
* \brief Retrieves the name label for the journal from the configuration file.
*
* This function opens the `star.ini` configuration file located in the `.\config` directory and reads the first line, expected to contain the name label for the journal. The label is used as part of the document titling process.
*
* \return A string containing the name label for the journal.
* \note This function, along with get_database_path(), opens and reads the `star.ini` file separately. If performance becomes a concern or if additional configuration settings are added, consider optimizing to parse the file once and cache all needed values.
*/
string get_star_name() {
    ifstream star_rc(R"(.\config\star.ini)");
    string line;
    getline(star_rc, line);
    print("get_star_name()");
    print(line);
    return line;
}

/*!
* \brief Retrieves the database path from the configuration file.
*
* This function opens the `star.ini` configuration file located in the `.\config` directory and reads the first line, which is expected to contain the name label for the journal.
*
* \return A string containing the name label for the journal.
* \note This function, along with get_star_name(), opens and reads the `star.ini` file separately. If performance becomes a concern or if additional configuration settings are added, consider optimizing to parse the file once and cache all needed values.
*/
string get_database_path() {
    ifstream star_rc(R"(.\config\star.ini)");
    string line;
    getline(star_rc, line);
    getline(star_rc, line);
    print("get_database_path()");
    print(line);
    return line;
}

/*!
* @brief Retrieves the current episode number from the database.
* 
* Connects to the SQLite database to fetch the latest episode number,
* incrementing it for the next use. Ensures unique identification for each journal entry.
* 
* \note hmm 
* \return The episode number before incrementing, or -1 if an error occurs.
* \note Error handling is implemented to return -1 if any step in the database interaction fails.
* This simple error handling strategy should be enhanced for applications requiring more robust database operations.
* \note The static variable `db_path` is used to store the database path from `get_database_path()`, reducing the need to read the configuration file multiple times. This is particularly beneficial for performance when multiple episode numbers are retrieved during a single program execution.
*/
static int get_episode_number() {
    static string db_path = get_database_path();
    sqlite3* db;
    sqlite3_stmt* selectStmt;
    sqlite3_stmt* updateStmt;
    int rc = sqlite3_open(db_path.c_str(), &db);
    if (rc != SQLITE_OK) {
        return -1;
    }
    const char* selectSQL = "select * from counter limit 1;";
    rc = sqlite3_prepare_v2(db, selectSQL, -1, &selectStmt, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(selectStmt);
        sqlite3_close(db);
        return -1;
    }
    int episode_number;
    if (sqlite3_step(selectStmt) == SQLITE_ROW) {
        episode_number = sqlite3_column_int(selectStmt, 0);
    }
    else {
        episode_number = -1;
    }
    sqlite3_finalize(selectStmt);
    if (episode_number != -1) {
        const char* updateSQL = "update counter set value = ?;";
        rc = sqlite3_prepare_v2(db, updateSQL, -1, &updateStmt, nullptr);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(updateStmt);
            sqlite3_close(db);
            return episode_number;
        }
        sqlite3_bind_int(updateStmt, 1, episode_number + 1);
        if (sqlite3_step(updateStmt) != SQLITE_DONE) {
        }
        sqlite3_finalize(updateStmt);
    }
    sqlite3_close(db);
    return episode_number;
}

/*!
* @brief Generates a title for the current episode.
*
* This function creates the episode title using the current episode number and timestamps, encapsulating the formatting logic for journal titles. It uses a static variable to cache the name label of the journal, ensuring the label is loaded only once per program execution.
* 
* \return A string containing the formatted episode title.
* \note The use of a static variable for the journal name ensures that `get_star_name()` is called no more than once, optimizing performance by avoiding repeated file reads. This approach assumes the journal name remains constant during the program's lifetime.
*/
static string get_episode_title() {
    static string star_name = get_star_name();
    oss s;
    s << star_name << ' ' << get_episode_number() << '\n' << get_datestamp() << "\n\n" << get_timestamp();
    return s.str();
}

/*!
* @brief Prints and saves the title of the current episode. Hey
*
* This function calls `get_episode_title` to generate the episode title, then prints it to the screen
* using the `print_to_screen` function defined in main.h, and finally saves the document using `save_file`.
*
* \see get_episode_title
* \see save_file
* \see print_to_screen() in main.h for output details.
* \runtime
*/
void print_episode_title() {
    string episode_title = get_episode_title();
    print_to_screen(episode_title);
    save_file();
}