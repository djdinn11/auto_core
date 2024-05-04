/*!
\file thread.ixx
\brief This provides a template for error handling in threads.
\hardlink
*/
export module thread;
import base;
import print;
import <Windows.h>;

export template<typename Func>
void run_with_exception_handling(Func func) {
    try {
        func();
    }
    catch (const exception& e) {
        print("caught exception: {}", e.what());
    }
    catch (...) {
        print("crash in thread function");
    }
}