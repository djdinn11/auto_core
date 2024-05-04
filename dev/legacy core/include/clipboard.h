#pragma once
#include <base.h>

void set_clipboard_text(const wstring& text);
wstring get_clipboard_text();
void paste_from_clipboard();