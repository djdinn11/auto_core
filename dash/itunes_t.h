#pragma once
#include <visual.h>
#include <itunes.h>

void iTunes_next_song();

extern condition_variable iT_cv;
extern bool iT_playback_state_change;