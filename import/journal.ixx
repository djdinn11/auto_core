/*!
\file journal.ixx
\brief Follows the 'dice roll' method to generate a random number or prompt for journaling inspiration.
*/
export module journal;
import visual;
import keyboard;
import thread;
import main;
import <Windows.h>;

export {
    void print_Eric_choice();
    void print_Katrina_choice();
    void print_Lily_choice();
    void print_Star_choice();
    void print_Luna_choice();
    void print_Daniel_choice();
    void print_Jose_choice();
    void print_Tabby_choice();
}

int upper_choice;
string choice_selector;

int get_random_number(int range_low, int range_high) {
    static mt19937 engine {random_device{}()};
    uniform_int_distribution<int> dist(range_low, range_high);
    return dist(engine);
}
void set_number_of_choices() {
    HWND currentWindowHandle = GetForegroundWindow();
    set_focus_auto_core();
    string choice_selection;
    string choice_number_str;
    printnl("Enter number of choices: ");
    getline(cin, choice_number_str);
    if (choice_number_str.empty()) {
        upper_choice = 2;
        logg("");
    }
    else {
        logg("{}", choice_number_str);
        try {
            int choice_number = stoi(choice_number_str);
            if (choice_number >= 2) {
                upper_choice = choice_number;
            }
            else if (choice_number == 1 || choice_number == 0) {
                upper_choice = 1;
            }
        }
        catch (...) {
            upper_choice = 2;
        }
    }
    SetForegroundWindow(currentWindowHandle);
}
void thread_print_choice_with_name() {
    set_number_of_choices();
    int random_choice_number = get_random_number(1, upper_choice);
    print_to_screen(format("{} selects {}.", choice_selector, random_choice_number));
}
void thread_print_choice_with_zero() {
    set_number_of_choices();
    int random_choice_number = get_random_number(0, upper_choice);
    print_to_screen(format("{} selects {}.", choice_selector, random_choice_number));
}

export void print_choice(const string& name, bool include_zero) {
    choice_selector = name;
    if (include_zero) {
        thread t([=]() {run_with_exception_handling(thread_print_choice_with_zero); });
        t.detach();
    }
    else {
        thread t([=]() {run_with_exception_handling(thread_print_choice_with_name); });
        t.detach();
    }
}
export function<void()> make_print_choice(const string& name, bool include_zero) {
    return [=]() {print_choice(name, include_zero);};
}

/** \runtime */
void print_Tabby_choice() {
    choice_selector = "Tabby";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_zero); });
    t.detach();
}

/** \runtime */
void print_Eric_choice() {
    choice_selector = "Eric";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_zero); });
    t.detach();
}

/** \runtime */
void print_Katrina_choice() {
    choice_selector = "Katrina";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_zero); });
    t.detach();
}

/** \runtime */
void print_Lily_choice() {
    choice_selector = "Lily";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_name); });
    t.detach();
}

/** \runtime */
void print_Star_choice() {
    choice_selector = "Star";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_zero); });
    t.detach();
}

/** \runtime */
void print_Luna_choice() {
    choice_selector = "Luna";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_name); });
    t.detach();
}

/** \runtime */
void print_Daniel_choice() {
    choice_selector = "Daniel";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_name); });
    t.detach();
}

/** \runtime */
void print_Jose_choice() {
    choice_selector = "Jose";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_zero); });
    t.detach();
}