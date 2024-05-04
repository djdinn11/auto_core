/*!
\file logger_w.h
\brief Logs system wake events, extending Windows' native logging to offer historical wake event tracking.

By polling system information, this module provides detailed logging of wake events, aiding in the analysis of system behavior and Auto Core's interaction with the host machine.
*/
#pragma once
#include <logger.h>

void log_last_wake();