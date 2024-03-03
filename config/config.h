#pragma once
#include <visual.h>
#include <choice.h>
#include <clock.h>
#include <dash.h>
#include <itunes.h>
#include <keyboard.h>
#include <main.h>
#include <numkey.h>
#include <spotify.h>
#include <slash.h>
#include <star.h>
#include <taskbar.h>

struct function_state {
    function<void()> primary;
    function<void()> secondary;
};

extern unordered_map<int, function_state> ac_numkey_event;

void parse_and_set_action_map();

struct set_state {
    int key;
    function<void()> primary;
    function<void()> secondary;
};