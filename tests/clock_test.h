#pragma once
#pragma once
#include <windows.h>
#include <chrono>
#include <locale>
#include <string>
#include <ostream>
#include <sstream>

using oss = std::ostringstream;
namespace chrono = std::chrono;
using std::string;
using std::to_string;
using std::runtime_error;
using std::runtime_error;

tm get_local_time();
int get_minutes_stamp();
int get_current_seconds();
string get_timestamp();
string get_datestamp();
string get_timestamp_with_seconds();
string get_datetime_stamp_with_seconds();
string get_datetime_stamp_for_logger();
string set_timestamp_with_seconds(int hour, int min, int sec);
string set_datestamp(int mon, int day, int year);

#include <visual.h>
using std::ifstream;
using std::ofstream;



#include <iostream>


static tm get_local_time() {
    auto now = chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now);
    tm local_tm;
    if (localtime_s(&local_tm, &now_c) != 0) {
        throw runtime_error("Failed to get local time.");
    }
    return local_tm;
}
//auto now = chrono::system_clock::now();
//auto now_c = chrono::system_clock::to_time_t(now);
//tm local_tm;
//localtime_s(&local_tm, &now_c);
//
//static tm get_local_time() {
//    time_t t_time;
//    time(&t_time);
//    tm t;
//    if (localtime_s(&t, &t_time) != 0) {
//        throw runtime_error("Failed to get local time.");
//    }
//    return t;
//}
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
string set_timestamp_with_seconds(int hour, int min, int sec) {
    oss timestamp;
    timestamp << format_hour(hour) << ':'
        << format_minutes(min) << ':'
        << format_seconds(sec);
    return timestamp.str();
}
string set_datestamp(int mon, int day, int year) {
    oss datestamp;
    datestamp << mon + 1 << '-'
        << day << '-'
        << year % 100;
    return datestamp.str();
}
void maintainability() {
    int seconds_to_sleep = 60 - get_current_seconds();
    string timestamp = get_timestamp_with_seconds();
    string current_datestamp = get_datestamp();
}
void performance() {
    tm t = get_local_time();
    int seconds_to_sleep = 60 - t.tm_sec;
    string timestamp = set_timestamp_with_seconds(t.tm_hour, t.tm_min, t.tm_sec);
    string datestamp = set_datestamp(t.tm_mon, t.tm_mday, t.tm_year);
}
int clock_speed_micro_maintainability() {
    auto start = std::chrono::high_resolution_clock::now();
    maintainability();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by maintainability: " << duration.count() << " microseconds" << std::endl;
    return static_cast<int>(duration.count());

}
int clock_speed_micro_performance() {
    auto start = std::chrono::high_resolution_clock::now();
    performance();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by performance: " << duration.count() << " microseconds" << std::endl;
    return static_cast<int>(duration.count());
}
int clock_speed_nano_maintainability() {
    auto start = std::chrono::high_resolution_clock::now();
    maintainability();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time taken by maintainability: " << duration.count() << " nanoseconds" << std::endl;
    return static_cast<int>(duration.count());
}
int clock_speed_nano_performance() {
    auto start = std::chrono::high_resolution_clock::now();
    performance();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time taken by performance: " << duration.count() << " nanoseconds" << std::endl;
    return static_cast<int>(duration.count());
}

int main_test() {
    int maintainable_nano = clock_speed_nano_maintainability();
    int performance_nano = clock_speed_nano_performance();
    int total_gain_nano = 0;
    for (int i = 0; i < 25; i++) {
        maintainable_nano = clock_speed_nano_maintainability();
        performance_nano = clock_speed_nano_performance();
        int round_results = maintainable_nano - performance_nano;
        total_gain_nano += round_results;
        print("A gain of {} nanoseconds", round_results);
    }
    print("Total gain of {} nanoseconds", total_gain_nano);

    int maintainable_micro = clock_speed_micro_maintainability();
    int performance_micro = clock_speed_micro_performance();
    int total_gain_micro = 0;
    for (int i = 0; i < 25; i++) {
        maintainable_micro = clock_speed_micro_maintainability();
        performance_micro = clock_speed_micro_performance();
        int round_results = maintainable_micro - performance_micro;
        total_gain_micro += round_results;
        print("A gain of {} microseconds", round_results);
    }
    print("Total gain of {} microseconds", total_gain_micro);
    return 0;
}