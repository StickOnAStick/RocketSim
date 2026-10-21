#include <print>
#include <csignal>
#include <unistd.h> // Required header

#include "quill/Backend.h"

#include "app/app.h"

namespace {
    volatile std::sig_atomic_t signalStatus = 0;
    volatile std::sig_atomic_t signalRecoverable = 0;
}

void _sig_handler(int sig);
void _start_logger();
void _stop_logger();


int main(int argc, char* argv[]) {
    std::signal(SIGINT, _sig_handler);
    std::signal(SIGABRT, _sig_handler);
    std::signal(SIGQUIT, _sig_handler);
    _start_logger();

    App::App app;

    while(!signalStatus) {
        std::println("Waiting");
        sleep(1);
    }

    std::println("Stopping quill...\n");
    _stop_logger();
}

void _sig_handler(int sig) {
    signalStatus = sig;

    switch (signalStatus) {
        case SIGINT:
        case SIGABRT:
        case SIGQUIT: 
            signalRecoverable = 1;
            break;
        default:
            std::print("Unhandled signal {}\n", static_cast<int>(signalStatus));
            std::exit(1);
            break;
    }
    
}

void _start_logger(){
    quill::Backend::start();
}

void _stop_logger(){
    quill::Backend::stop();
}