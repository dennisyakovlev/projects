#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "monitor_path.h"

namespace monitor {

void monitor (std::string& dir) {
    monitor(dir.c_str());
}

void monitor(const std::string& dir) {
    monitor(dir.c_str());
}

void monitor(std::string&& dir) {
    monitor(dir.c_str());
}

void monitor(std::string* dir) {
    monitor(dir->c_str());
}

void monitor(const char* dir) {    
    int fd[2];
    pipe(fd);
    pid_t to_stop = getpid();

    int i = fork();
    // child continues until monitored folder is written to
    if (i == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execl("/usr/bin/inotifywait", "/usr/bin/inotifywait", dir, "-e",  "create", "-e", "", "-q", nullptr);
        ::perror("probably either wrong dir or cannot find /usr/bin/inotifywait");
    } else if (i > 0) {
        i = fork();
        if (i == 0) {
            close(fd[1]);

            char buf[monitor::buf_sz];
            buf[monitor::buf_sz - 1] = '\0';
            int num_read;
            num_read = read(fd[0], &buf, monitor::buf_sz - 1);
            kill(to_stop, SIGINT);

            if (num_read == -1) {
                ::perror("read");
                _exit(1);
            }

            close(fd[0]);
            _exit(0);
        } else if (i == -1) {
            ::perror("inner fork");
            _exit(1);
        }
    } else {
        ::perror("fork");
    }
}

};