#pragma once

class Taskbar {
public:
	int auto_core = 1;
	int folder    = 2;
	int word      = 3;
	int itunes    = 4;
	int chrome    = 5;
	int visual    = 6;
	int discord   = 7;
	int taskbar_8 = 8;
	int taskbar_9 = 9;
	int taskbar_0 = 10;
};

void activate_Auto_Core();
void activate_Folder();
void activate_Word();
void activate_iTunes();
void activate_Chrome();
void activate_Visual();
void activate_Discord();
void activate_Taskbar_8();

extern Taskbar taskbar;