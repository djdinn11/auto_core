import base;
import logger_s;
#pragma warning(disable:4251)
#pragma warning(disable:4275)
import <CivetServer.h>;

CivetServer* server;

void start_server() {
    const char* options[] = {
        "document_root", R"(.\server)",
        "listening_ports", port_number_str.c_str(),
        NULL
    };
    try {
        server = new CivetServer(options);
        server_logg_and_logg("server started on port {}", options[3]);
        while (true) {
            this_thread::sleep_for(chrono::seconds(60));
        }
    }
    catch (exception& e) {
        server_logg_and_print("Exception caught in server: {}", e.what());
        exit(1);
    }
}

int main() {
    server_log_init();
    start_server();
    server_logg_and_print("If you are seeing this in a log file, then a bonus was discovered.\nGo to server.cxx, and take a look at the comment.\nThe comment reads:\n// This line will likely never be reached");
    return 0; // This line will likely never be reached
}
