/*!
\file server.h
\brief Sets up a local server for Auto Core, enabling web-based local file access.

This module facilitates the interaction with local files through a browser interface, broadening the scope of Auto Core's automation capabilities.
*/
#pragma once
#include <visual.h>

bool start_server();
void stop_server();