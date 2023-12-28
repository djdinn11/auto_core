#include <iostream>
#include <sqlite3.h>

int main() {
    sqlite3* db;
    char* errMsg = 0;
    int result;

    // Open or create the database file named star.db
    result = sqlite3_open("star.db", &db);

    if (result) {
        std::cerr << "Error opening/creating the database: " << sqlite3_errmsg(db) << std::endl;
        return result;
    }
    else {
        std::cout << "Opened/created database successfully" << std::endl;
    }

    // SQL query to create a table named 'counter' with a single integer column 'value'
    const char* sql = "CREATE TABLE IF NOT EXISTS counter (value INTEGER);";

    // Execute the SQL query to create the table
    result = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "Table created successfully" << std::endl;
    }

    // Insert an initial value of 1 into the 'value' column
    const char* insertSQL = "INSERT INTO counter (value) VALUES (1);";

    result = sqlite3_exec(db, insertSQL, 0, 0, &errMsg);

    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "Initial value inserted successfully" << std::endl;
    }

    // Close the database connection
    sqlite3_close(db);

    return 0;
}
