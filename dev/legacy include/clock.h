/*!
\file clock.h
\brief Offers clock and timing functionalities for Auto Core, including timestamping and timers.

This module enables Auto Core to interact with system time, offering functionalities for retrieving current timestamps,
creating datestamps, and managing timers. Useful for time-based automation and logging.
*/
#pragma once
#include <base.h>

int get_minutes_stamp();
int get_current_seconds();
string get_timestamp();
string get_datestamp();
string get_timestamp_with_seconds();
string get_datetime_stamp_with_seconds();
string get_datetime_stamp_for_logger();
string get_day_of_week();