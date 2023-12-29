#include <taskbar.h>
#include <keyboard.h>

Taskbar taskbar;

void activate_Auto_Core()   {send_winkey(taskbar.auto_core);}
void activate_Folder()      {send_winkey(taskbar.folder);}
void activate_Word()        {send_winkey(taskbar.word);}
void activate_iTunes()      {send_winkey(taskbar.itunes);}
void activate_Chrome()      {send_winkey(taskbar.chrome);}
void activate_Visual()      {send_winkey(taskbar.visual);}
void activate_Discord()     {send_winkey(taskbar.discord);}
void activate_Firefox()     {send_winkey(taskbar.firefox);}
void activate_Taskbar_9()   {send_winkey(taskbar.taskbar_9);}
void activate_Taskbar_10()  {send_winkey(taskbar.taskbar_10);}