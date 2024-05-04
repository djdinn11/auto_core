/*!
\file slash.h
\brief Manages the emptying of the Recycle Bin and logs deleted items, adding a layer of automation to system maintenance tasks.

Through this module, Auto Core can automate the clearing of the Recycle Bin, with detailed logging of the process for user review.
\note This module calls slash.exe
*/
#pragma once
#include <visual.h>

void retrieve_and_delete_recycle_bin();