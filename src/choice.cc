#include <choice.h>
#include <random>
#include <keyboard.h>
#include <taskbar.h>
#include <main.h>

using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;
int upper_choice;
string choice_selector;

int get_random_number(int range_low, int range_high) {
    static mt19937 engine{random_device{}()};
    uniform_int_distribution<int> dist(range_low, range_high);
    return dist(engine);
}
void thread_print_choice_prompt() {
    HWND currentWindowHandle = GetForegroundWindow();
    set_focus_auto_core();
    string choice_prompt =  "Choice Prompt:\n";
    string prompt;
    int choice_number = 1;
    while (true) {
        printnl("{}=", choice_number);
        getline(cin, prompt);
        if (prompt.empty()) {
            choice_number  -= 1;
            break;
        }
        choice_prompt += format("{} = {}\n", choice_number, prompt);
        choice_number++;
    }
    if (choice_number <= 1) {
        choice_number = 2;
    }
    int random_choice_number = get_random_number(0, choice_number);
    choice_prompt += format("Star selects {}.", random_choice_number);
    SetForegroundWindow(currentWindowHandle);
    print_to_screen(choice_prompt);
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
    int random_choice_number = get_random_number(0, upper_choice);
    print_to_screen(format("{} selects {}.", choice_selector, random_choice_number));
}
void thread_print_choice_with_zero() {
    set_number_of_choices();
    int random_choice_number = get_random_number(1, upper_choice);
    print_to_screen(format("{} selects {}.", choice_selector, random_choice_number));
}
void print_choice_display() {
    thread t([=]() {run_with_exception_handling(thread_print_choice_prompt);});
    t.detach();
}
void print_Eric_choice() {
    choice_selector = "Eric";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_zero);});
    t.detach();
}
void print_Katrina_choice() {
    choice_selector = "Katrina";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_zero);});
    t.detach();
}
void print_Lily_choice() {
    choice_selector = "Lily";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_name);});
    t.detach();
}
void print_Star_choice() {
    choice_selector = "Star";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_name);});
    t.detach();
}
void print_Luna_choice() {
    choice_selector = "Luna";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_name);});
    t.detach();
}
void print_Daniel_choice() {
    choice_selector = "Daniel";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_name);});
    t.detach();
}
void print_Jose_choice() {
    choice_selector = "Jose";
    thread t([=]() {run_with_exception_handling(thread_print_choice_with_zero);});
    t.detach();
}