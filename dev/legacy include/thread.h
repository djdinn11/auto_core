#pragma once

template<typename Func>
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