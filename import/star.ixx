/*!
\file star.ixx
\brief Assists in the file creation and management of journaling documents within Auto Core.
*/
export module star;
import visual;
import cloud;
import <sqlite3.h>;
import <Windows.h>;

export {
    void print_episode_title();
}

void save_file() {
    INPUT inputs[4] = {};
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

string get_star_name() {
    logg("get_star_name()");
    ifstream star_rc(R"(.\config\star.ini)");
    string line;
    getline(star_rc, line);
    logg(line);
    return line;
}
string get_database_path() {
    logg("get_database_path()");
    ifstream star_rc(R"(.\config\star.ini)");
    string line;
    getline(star_rc, line);
    getline(star_rc, line);
    logg(line);
    return line;
}
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
static string get_episode_title() {
    static string star_name = get_star_name();
    string star_and_number = format("{} {}", star_name, get_episode_number());
    update_string_in_firebase(star_and_number);
    oss s;
    s << star_and_number << '\n' << get_datestamp() << "\n\n" << get_timestamp();
    return s.str();
}

/*!
* \runtime
*/
void print_episode_title() {
    string episode_title = get_episode_title();
    print_to_screen(episode_title);
    save_file();
}