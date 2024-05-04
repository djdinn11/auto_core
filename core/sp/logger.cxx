module logger;
import logger_c;
import sp_x;

void log_init() {
	update_main_log_file();
	sp_logger.logg_and_logg("sp_ac.exe started");
}