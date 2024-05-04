#include <clock.h>
#include <config.h>

SYSTEMTIME get_local_time() {
    SYSTEMTIME st;
    GetLocalTime(&st);
    return st;
}
static string format_hour(int hour) {
    oss hour_str;
    if (hour < config.end_of_day) {
        hour += 24;
    }
    else if (hour < 10) {
        hour_str << '0';
    }
    else if (hour >= 13 && hour < 22) {
        hour -= 12;
    }
    hour_str << hour;
    return hour_str.str();
}
static string format_minutes(int minutes) {
    oss minutes_str;
    if (minutes < 10) {
        minutes_str << '0';
    }
    minutes_str << minutes;
    return minutes_str.str();
}
static string format_seconds(int seconds) {
    oss seconds_str;
    if (seconds < 10) {
        seconds_str << '0';
    }
    seconds_str << seconds;
    return seconds_str.str();
}
string get_timestamp() {
    SYSTEMTIME st = get_local_time();
    oss timestamp;
    timestamp << format_hour(st.wHour) << ':'
        << format_minutes(st.wMinute);
    return timestamp.str();
}
string get_timestamp_with_seconds() {
    SYSTEMTIME st = get_local_time();
    oss timestamp;
    timestamp << format_hour(st.wHour) << ':'
        << format_minutes(st.wMinute) << ':'
        << format_seconds(st.wSecond);
    return timestamp.str();
}
string get_datestamp() {
    SYSTEMTIME st = get_local_time();
    oss datestamp;
    datestamp << st.wMonth << '-'
        << st.wDay << '-'
        << st.wYear % 100;
    return datestamp.str();
}
string get_datetime_stamp_with_seconds() {
    oss datetime_stamp;
    datetime_stamp << get_timestamp_with_seconds() << " on " << get_datestamp();
    return datetime_stamp.str();
}
string get_datetime_stamp_for_logger() {
    oss datetime_stamp;
    datetime_stamp << get_datestamp() << " at " << get_timestamp_with_seconds();
    return datetime_stamp.str();
}
int get_minutes_stamp() {
    SYSTEMTIME st = get_local_time();
    return st.wHour * 60 + st.wMinute;
}
int get_current_seconds() {
    SYSTEMTIME st = get_local_time();
    return st.wSecond;
}
string get_day_of_week() {
    SYSTEMTIME st = get_local_time();
    GetLocalTime(&st);
    const char* days_of_week[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    string day_of_week = days_of_week[st.wDayOfWeek];
    return format("Today is {}", day_of_week);
}