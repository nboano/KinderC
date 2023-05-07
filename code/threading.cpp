#include "../kinderc.hpp"
#pragma once

Thread::Thread(void(*fn_handler)(void*)) {
    if((String)JavaScript::Eval("'SharedArrayBuffer' in window") == "false") {
        throw Exception("Threads are not available in this context.\nEnsure that the SharedArrayBuffer object is instantiable.");
    }

    if(worker_path == nullptr) {
        throw Exception("Must specify the Threads worker path by calling Thread::SetWorkerPath(...)");
    }

    internal_handler = Handler(fn_handler);
}

void Thread::SetWorkerPath(const char* workerPath) {
    worker_path = (char*)workerPath;
}

void Thread::Start(void* opt_pointer) {
    JavaScript::Eval("let w = new Worker('%s');w.postMessage([%i, %i, memory, \"%s\"]);w.onmessage=worker_invoke;", worker_path, internal_handler.LambdaIndex, opt_pointer, $("assembly[src]").getAttribute("src"));
}

void Thread::Sleep(int milliseconds) {
    double start = microtime();
    while (start + milliseconds >= microtime());
}

void Thread::InvokeMain(void(*fn_handler)(void*)) {
    Handler invoke_handler = Handler(fn_handler);

    JavaScript::Eval("self.postMessage([%i])", invoke_handler.LambdaIndex);
}