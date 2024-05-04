module logger;
import logger_c;
import itunes_x;

void log_init() {
	update_main_log_file();
	iTunes_logger.logg_and_logg("ac_itunes.exe started");
}