#include <choice.h>
#include <random>
#include <limits>

int getRandomNumber(int range_low, int range_high) {
    static mt19937 engine{random_device{}()};
    uniform_int_distribution<int> dist(range_low, range_high);
    return dist(engine);
}
void print_Star_choice() {
    int choice_number = getRandomNumber(1, 3);
    string select_msg = f("Star selects {}.\n", choice_number);
    print_to_screen(select_msg);
}
void print_Lily_choice() {
    int choice_number = getRandomNumber(1, 3);
    string select_msg = f("Luna selects {}.\n", choice_number);
    print_to_screen(select_msg);
}