/*!
\file auto_core.h
\brief Entry point for the Auto Core project, designed for Windows 11 systems.

This header initiates Auto Core, which is aimed at enhancing user productivity through automation.
Each deployment of Auto Core might require modifications specific to the user's environment or needs.
Provides foundational functionalities and sets up the environment for other modules to operate effectively.
*/
#pragma once
#include <core.h>

struct function_state {
    function<void()> primary;
    function<void()> secondary;
};
extern unordered_map<int, function_state> ac_numkey_event;

