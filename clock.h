#pragma once
#include <visual.h>

extern int minutes_stamp;
extern string timestamp;
extern string datestamp;

tm get_local_time();
string get_timestamp();
void set_minutes_stamp(int hour, int min);
void set_minutes_stamp();
void set_timestamp(int hour, int min);
void set_timestamp();
void set_datestamp(int month, int day, int year);
void set_datestamp();
void set_time();