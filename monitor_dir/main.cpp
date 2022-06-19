#include <monitor_path.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>

void handle(int i) {
    std::cout << "detected change in dir\n";
    kill(0, SIGKILL);
}

int main(int argc, char const *argv[]) {
    monitor::monitor(argv[1]);

    // create a file or sum inside direcotry and watch program "terminate"
    sigset_t signal_set;
    sigemptyset(&signal_set);

    struct sigaction act;
    act.sa_handler = handle;
    act.sa_mask = signal_set;
    act.sa_restorer = nullptr;
    act.sa_flags = 0;

    sigaction(SIGINT, &act, nullptr);

    while (true) {}
    
    return 0;
}
