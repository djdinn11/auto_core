#pragma once
#include <encoding.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <print>
#include <format>

using namespace std;

using ss = stringstream;
using oss = ostringstream;
using wss = wostringstream;

#define f format

void print(const std::string& s);