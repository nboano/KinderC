#pragma once
#include "../kinderc.hpp"

class Thread {
    private:
    Handler internal_handler = Handler("");

    static char* worker_path;

    public:

    Thread(void(*fn_handler)(void*));

    void Start(void* opt_pointer = nullptr);

    static void SetWorkerPath(const char* workerPath);
    
    static void Sleep(int milliseconds);

    static void InvokeMain(void(*fn_handler)(void*));
};