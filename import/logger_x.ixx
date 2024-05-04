/*!
\file logger_x.ixx
\brief This module is for individual logging components, which have _x, such as itunes_x.ixx or sp_x.ixx
*/
export module logger_x;
import visual;
import sp;
import itunes;
import logger_c;
import <Windows.h>;

export void update_log_components() {
    update_sp_logger();
    update_iTunes_logger();
}