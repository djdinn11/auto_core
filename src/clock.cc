#include <clock.h>

static tm get_local_time() {
    auto now = chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now);
    tm local_tm;
    if (localtime_s(&local_tm, &now_c) != 0) {
        throw runtime_error("Failed to get local time.");
    }
    return local_tm;
}
static string format_hour(int hour) {
    oss hour_str;
    if (hour < 7) {
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
    tm t = get_local_time();
    oss timestamp;
    timestamp << format_hour(t.tm_hour) << ':'
        << format_minutes(t.tm_min);
    return timestamp.str();
}
string get_timestamp_with_seconds() {
    tm t = get_local_time();
    oss timestamp;
    timestamp << format_hour(t.tm_hour) << ':'
        << format_minutes(t.tm_min) << ':'
        << format_seconds(t.tm_sec);
    return timestamp.str();
}
string get_datestamp() {
    tm t = get_local_time();
    oss datestamp;
    datestamp << t.tm_mon + 1 << '-'
        << t.tm_mday << '-'
        << t.tm_year % 100;
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
    tm t = get_local_time();
    return t.tm_hour * 60 + t.tm_min;
}
int get_current_seconds() {
    tm t = get_local_time();
    return t.tm_sec;
}