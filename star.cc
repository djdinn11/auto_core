#include <star.h>
#include <clock.h>
#include <sqlite3.h>

string star_path_db = R"(C:\DJ\My Folder\Auto Core\star.db)";
string episode_title;
int episode_number;

void set_episode_number() {
    sqlite3* db;
    sqlite3_stmt* selectStmt;
    sqlite3_stmt* updateStmt;
    int rc = sqlite3_open(star_path_db.c_str(), &db);
    if (rc != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        episode_number = -1;
        return;
    }
    const char* selectSQL = "SELECT * FROM counter LIMIT 1;";
    rc = sqlite3_prepare_v2(db, selectSQL, -1, &selectStmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error preparing select statement: " << sqlite3_errmsg(db) << endl;
        episode_number = -1;
        sqlite3_finalize(selectStmt);
        sqlite3_close(db);
        return;
    }
    if (sqlite3_step(selectStmt) == SQLITE_ROW) {
        episode_number = sqlite3_column_int(selectStmt, 0);
    }
    else {
        cerr << "Error stepping through results: " << sqlite3_errmsg(db) << endl;
        episode_number = -1;
    }
    sqlite3_finalize(selectStmt);
    if (episode_number != -1) {
        const char* updateSQL = "UPDATE counter SET value = ?;";
        rc = sqlite3_prepare_v2(db, updateSQL, -1, &updateStmt, nullptr);
        if (rc != SQLITE_OK) {
            cerr << "Error preparing update statement: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(updateStmt);
            sqlite3_close(db);
            return;
        }
        sqlite3_bind_int(updateStmt, 1, episode_number + 1);
        if (sqlite3_step(updateStmt) != SQLITE_DONE) {
            cerr << "Error updating episode number: " << sqlite3_errmsg(db) << endl;
        }
        sqlite3_finalize(updateStmt);
    }
    sqlite3_close(db);
}
void set_episode_title() {
    set_episode_number();
    set_time();
    ss s;
    s << "Star " << episode_number << "\r\n"
        << datestamp << "\n\n" << timestamp << "\n";
    episode_title = s.str();
}
void print_episode_title() {
    set_episode_title();
    print_to_screen(episode_title);
    simulate_save();
}