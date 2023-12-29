#include <clock.h>

int minutes_stamp;
string timestamp;
string datestamp;

tm get_local_time() {
    time_t t_time;
    time(&t_time);
    tm t;
    localtime_s(&t, &t_time);
    return t;
}
void set_minutes_stamp(int hour, int min) {
    minutes_stamp = hour * 60 + min;
}
void set_minutes_stamp() {
    tm t = get_local_time();
    set_minutes_stamp(t.tm_hour, t.tm_min);
}
void set_timestamp(int hour, int min) {
    string hour_str;
    if (hour > 12 && hour < 22) {
        hour -= 12;
        hour_str = to_string(hour);
    }
    else if (hour == 0) {
        hour = 24;
        hour_str = to_string(hour);
    }
    else if (hour < 10) {
        hour_str = f("0{}", hour);
    }
    else {
        hour_str = to_string(hour);
    }
    ss s;
    s << hour_str << ":" << setw(2) << setfill('0') << min;
    timestamp = s.str();
}
void set_timestamp() {
    tm t = get_local_time();
    set_timestamp(t.tm_hour, t.tm_min);
}
string get_timestamp() {
    tm t = get_local_time();
    set_timestamp(t.tm_hour, t.tm_min);
    return timestamp;
}
void set_datestamp(int month, int day, int year) {
    ss s;
    s << month + 1 << "-" << day << "-" << year % 100;
    datestamp = s.str();
}
void set_datestamp() {
    tm t = get_local_time();
    set_datestamp(t.tm_mon, t.tm_mday, t.tm_year);
}
void set_time() {
    tm t = get_local_time();
    set_minutes_stamp(t.tm_hour, t.tm_min);
    set_timestamp(t.tm_hour, t.tm_min);
    set_datestamp(t.tm_mon, t.tm_mday, t.tm_year);
}
void print_timestamp() {
    string timestamp = get_timestamp() + "\n";
    print_to_screen(timestamp);
}