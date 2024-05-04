#pragma once
#include <Windows.h>
#include <string>
#include <chrono>
#include <locale>
#include <ostream>
#include <sstream>
#include <exception>
#include <format>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <exception>
#include <conio.h>
#include <array>
#include <exception>
#include <functional>
#include <iomanip>
#include <istream>
#include <ostream>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <random>

namespace chrono = std::chrono;

namespace fs = std::filesystem;
using std::ios;
using std::ios_base;

namespace this_thread = std::this_thread;
using std::thread;
using std::mutex;
using std::condition_variable;
using std::unique_lock;

using ss = std::stringstream;
using iss = std::istringstream;
using oss = std::ostringstream;
using wss = std::wostringstream;
using std::ifstream;
using std::ofstream;

using std::cerr;
using std::cin;
using std::cout;
using std::wcout;
using std::getline;

using std::string;
using std::wstring;
using std::to_string;

using std::format;
using std::format_error;
using std::invalid_argument;
using std::vformat;
using std::make_format_args;
using std::forward;
using std::endl;

using std::array;
using std::vector;
using std::unordered_map;

using std::function;
using std::setw;
using std::setfill;
using std::exception;

using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;