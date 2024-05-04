export module itunes_x;
import logger;
import logger_c;

export Logger iTunes_logger("itunes");
export void update_iTunes_logger();

void update_iTunes_logger() {
	update_main_log_file();
	iTunes_logger.update_log_file();
}