import <iostream>;
import <filesystem>;
import <fstream>;
import <string>;
import <Windows.h>;

namespace fs = std::filesystem;
using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::getline;

const string hard_link_directory = R"(C:\DJ\My Folder\Auto Core\include\)";

bool create_hard_link(const string& filepath) {
    string link_name = "";
    size_t last_backslash_pos = filepath.rfind('\\');
    if (last_backslash_pos != string::npos) {
        cout << "Rightmost backslash found" << endl;
        link_name = filepath.substr(last_backslash_pos + 1);
    }
    string hard_link_filepath = hard_link_directory + link_name;
    if (CreateHardLinkA(hard_link_filepath.c_str(), filepath.c_str(), NULL)) {
        cout << "Hard link created successfully." << endl;
        return true;
    }
    else {
        cerr << "Failed to create hard link. Error: " << GetLastError() << endl;
        return false;
    }
}
void parse_for_hard_link(const string& filepath) {
    ifstream file(filepath);
    string line;
    while (getline(file, line)) {
        if (line.find(R"(\hardlink)") != string::npos) {
            cout << "hardlink found" << endl;
            create_hard_link(filepath);
            break;
        }
    }
    file.close();
}
void process_file(ofstream& runtime_file, const string& filepath) {
    cout << filepath << endl;
    ifstream file(filepath);
    string line;
    while (getline(file, line)) {
        if (line.find(R"(\runtime)") != string::npos) {
            cout << "Found \\runtime in: " << endl;
            string function_name;
            do {
                if (line.find(R"(*/)") != string::npos) {
                    cout << "Found */" << endl;
                    string function_line;
                    getline(file, function_line);
                    if (function_line.find("void ") != string::npos) {
                        size_t first_space = function_line.find(" ");
                        size_t parentheses = function_line.find("()");
                        function_name = function_line.substr(first_space + 1, parentheses - first_space - 1);
                        cout << function_name << endl;
                        break;
                    }
                }
            } while (getline(file, line));
            if (function_name != "") {
                runtime_file << "        {\"" << function_name << "\", &" << function_name + "},\n";
            }
        }
    }
    file.close();
}
void insert_make_print_code(ofstream& runtime_file) {
    runtime_file << "int get_numkey_vk_code(const string & vk_code_string) {\n"
        << "    static const unordered_map<string, int> numkey_vk_code_map = {\n"
        << "        {\"numkey_0\", numkey_0},\n"
        << "        {\"numkey_1\", numkey_1},\n"
        << "        {\"numkey_2\", numkey_2},\n"
        << "        {\"numkey_3\", numkey_3},\n"
        << "        {\"numkey_4\", numkey_4},\n"
        << "        {\"numkey_5\", numkey_5},\n"
        << "        {\"numkey_6\", numkey_6},\n"
        << "        {\"numkey_7\", numkey_7},\n"
        << "        {\"numkey_8\", numkey_8},\n"
        << "        {\"numkey_9\", numkey_9},\n"
        << "        {\"numkey_star\", numkey_star},\n"
        << "        {\"numkey_plus\", numkey_plus},\n"
        << "        {\"numkey_dot\", numkey_dot},\n"
        << "        {\"numkey_enter\", numkey_enter},\n"
        << "        {\"numkey_dash\", numkey_dash},\n"
        << "        {\"numkey_slash\", numkey_slash},\n"
        << "        {\"numkey_play_pause\", numkey_play_pause},\n"
        << "    };\n"
        << "    auto it = numkey_vk_code_map.find(vk_code_string);\n"
        << "    if (it != numkey_vk_code_map.end()) {\n"
        << "        return it->second;\n"
        << "    }\n"
        << "    else {\n"
        << "        return -1;\n"
        << "    }\n"
        << "}\n";
}

void insert_vk_code(ofstream& runtime_file) {
    runtime_file << "int get_numkey_vk_code(const string & vk_code_string) {\n"
        << "    static const unordered_map<string, int> numkey_vk_code_map = {\n"
        << "        {\"numkey_0\", numkey_0},\n"
        << "        {\"numkey_1\", numkey_1},\n"
        << "        {\"numkey_2\", numkey_2},\n"
        << "        {\"numkey_3\", numkey_3},\n"
        << "        {\"numkey_4\", numkey_4},\n"
        << "        {\"numkey_5\", numkey_5},\n"
        << "        {\"numkey_6\", numkey_6},\n"
        << "        {\"numkey_7\", numkey_7},\n"
        << "        {\"numkey_8\", numkey_8},\n"
        << "        {\"numkey_9\", numkey_9},\n"
        << "        {\"numkey_star\", numkey_star},\n"
        << "        {\"numkey_plus\", numkey_plus},\n"
        << "        {\"numkey_dot\", numkey_dot},\n"
        << "        {\"numkey_enter\", numkey_enter},\n"
        << "        {\"numkey_dash\", numkey_dash},\n"
        << "        {\"numkey_slash\", numkey_slash},\n"
        << "        {\"numkey_play_pause\", numkey_play_pause},\n"
        << "    };\n"
        << "    auto it = numkey_vk_code_map.find(vk_code_string);\n"
        << "    if (it != numkey_vk_code_map.end()) {\n"
        << "        return it->second;\n"
        << "    }\n"
        << "    else {\n"
        << "        return -1;\n"
        << "    }\n"
        << "}\n";
}

int main() {
    ofstream runtime_file(R"(..\..\src\dash.cxx)");
    runtime_file << "module dash;\n\n"
        << "function<void()> get_function_by_name(const string& function_name) {\n"
        << "    static const unordered_map<string, function<void()>> function_map = {\n";
    string path = R"(C:\DJ\My Folder\Auto Core\import)";
    try {
        if (fs::is_directory(path)) {
            for (const auto& entry : fs::directory_iterator(path)) {
                if (entry.is_regular_file()) {
                    process_file(runtime_file, entry.path().string());
                    parse_for_hard_link(entry.path().string());
                }
            }
        }
        else {
            cout << "Provided path is not a directory." << endl;
        }
    }
    catch (const fs::filesystem_error& e) {
        cerr << e.what() << endl;
    }
    runtime_file << "    };\n"
        << "    if (function_name.find(\"make_print_choice\") != string::npos) {\n"
        << "        size_t opening_quotation = function_name.find('\"');\n"
        << "        size_t closing_quotation = function_name.find(\"\\\",\");\n"
        << "        string choice_name = function_name.substr(opening_quotation + 1, closing_quotation - opening_quotation - 1);\n"
        << "        string bool_value_location = function_name.substr(closing_quotation);\n"
        << "        size_t bool_true_value = bool_value_location.find(\"true\");\n"
        << "        bool bool_value = false;\n"
        << "        if (bool_true_value != string::npos) {\n"
        << "            bool_value = true;\n"
        << "        }\n"
        << "        return make_print_choice(choice_name, bool_value);\n"
        << "    }\n"
        << "    else {\n"
        << "        auto it = function_map.find(function_name);\n"
        << "        if (it != function_map.end()) {\n"
        << "            return it->second;\n"
        << "        }\n"
        << "        else {\n"
        << "            return nullptr;\n"
        << "        }\n"
        << "    }\n"
        << "}\n";
    insert_vk_code(runtime_file);
    runtime_file.close();
    return 0;
}