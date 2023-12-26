#include <taskbar.h>
#include <keyboard.h>

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

void activate_Auto_Core()   {send_winkey(auto_core);}
void activate_Folder()      {send_winkey(folder);}
void activate_Word()        {send_winkey(word);}
void activate_iTunes()      {send_winkey(itunes);}
void activate_Chrome()      {send_winkey(chrome);}
void activate_Visual()      {send_winkey(visual);}
void activate_Discord()     {send_winkey(discord);}
void activate_Taskbar_8()   {send_winkey(taskbar_8);}