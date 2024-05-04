#include <base.h>
#include <logger_s.h>
#pragma warning(disable:4251)
#pragma warning(disable:4275)
#include <CivetServer.h>

CivetServer* server;

void start_server() {
    const char* options[] = {
        "document_root", R"(.\server)",
        "listening_ports", "8585",
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
    log_init();
    start_server();
    server_logg_and_print("server.exe - this line was reached\nsee comment at return 0 in main");
    return 0; // This line will likely never be reached
}
