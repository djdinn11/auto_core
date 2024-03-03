#include <server.h>
#pragma warning(disable:4251)
#pragma warning(disable:4275)
#include <CivetServer.h>

CivetServer* server;

void start_server() {
    const char* options[] ={
        "document_root", R"(C:\DJ\My Folder\Auto Core\server)",
        "listening_ports", "8585",
        NULL
    };
    logg("server started on port {}", options[3]);
    try {
        server = new CivetServer(options);
    }
    catch (const exception& e) {
        print("Failed to start server: {}", e.what());
    }
}
void run_server() {
    thread t(start_server);
    t.detach();
}