#include <logger_t.h>

Logger sp_logger("sp");

void update_sp_logger() {
	update_main_log_file();
	sp_logger.update_log_file();
}
void log_init() {
	update_main_log_file();
}