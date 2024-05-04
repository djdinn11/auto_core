export module sp_x;
import logger;
import logger_c;

export Logger sp_logger("sp");
export void update_sp_logger();

void update_sp_logger() {
	update_main_log_file();
	sp_logger.update_log_file();
}