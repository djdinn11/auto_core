/*!
\file clipboard.h
\brief Facilitates clipboard interactions for string handling within the Auto Core system.

To automate string insertion, Auto Core first copies a requested string
to the clipboard using set_clipboard_text, and then sends a 'ctrl + v'
command to paste from the clipboard into the open textbox.
*/
#pragma once
#include <base.h>

void set_clipboard_text(const wstring& text);
wstring get_clipboard_text();
void paste_from_clipboard();