#pragma once
#include <windows.h>
#include <chrono>
#include <locale>
#include <string>
#include <ostream>
#include <sstream>
#include <exception>

using oss = std::ostringstream;
namespace chrono = std::chrono;
using std::string;
using std::to_string;
using std::runtime_error;

int get_minutes_stamp();
int get_current_seconds();
string get_timestamp();
string get_datestamp();
string get_timestamp_with_seconds();
string get_datetime_stamp_with_seconds();
string get_datetime_stamp_for_logger();