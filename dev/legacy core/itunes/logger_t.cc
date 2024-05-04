#include <logger_t.h>

Logger iTunes_logger("itunes");

void update_iTunes_logger() {
	update_main_log_file();
	iTunes_logger.update_log_file();
}
void log_init() {
	update_main_log_file();
}