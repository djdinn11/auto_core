#include <print.h>
#include <clipboard.h>

void print(const string& s) {
    cout << s << endl;
    logg(s);
}
void printnl(const string& s) {
    cout << s;
    loggnl(s);
}
void print_to_screen(const string& msg) {
    print(msg);
    wss ws;
    ws << msg.c_str() << L"\n\n";
    set_clipboard_text(ws.str());
    paste_from_clipboard();
}