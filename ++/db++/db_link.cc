#include <iostream>
#include <sqlite3.h>

using namespace std;

int main() {
    sqlite3* db;
    char* errMsg = 0;
    int result;
    result = sqlite3_open("star.db", &db);
    if (result) {
        cerr << "Error opening/creating the database: " << sqlite3_errmsg(db) << endl;
        return result;
    }
    else {
        cout << "Opened/created database successfully" << endl;
    }
    const char* sql = "CREATE TABLE IF NOT EXISTS counter (value INTEGER);";
    result = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (result != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "Table created successfully" << endl;
    }
    const char* insertSQL = "INSERT INTO counter (value) VALUES (1);";
    result = sqlite3_exec(db, insertSQL, 0, 0, &errMsg);
    if (result != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "Initial value inserted successfully" << endl;
    }
    sqlite3_close(db);
    return 0;
}
