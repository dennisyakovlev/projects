#include <vector>
#include <array>
#include <pthread.h>

using write_cont_t = std::vector<int>;

constexpr unsigned long write_size = 100; // number of elements to write
constexpr unsigned long num_writes = 100; // number of times each thread writes write_size
constexpr unsigned long num_thread = 10; // number of threads

/*  thread_num - the give thread number
    num_writes - number of times writte to write_cont
    mutex - mutex of threads
    write_cont - container to modify
    thread - tid
*/
struct thread_arg {
    int thread_num;
    pthread_mutex_t* mutex;
    write_cont_t* write_cont;
    int num_writes = 0;
    pthread_t thread;
};

void* start_func(void* func_arg) {

    auto arg = reinterpret_cast<thread_arg*>(func_arg);

    while (arg->num_writes != num_writes) {
        ++(arg->num_writes);

        if (pthread_mutex_lock(arg->mutex) != 0) {
            std::perror("mutex lock");
        }

        for (auto i = 0; i != write_size; ++i) {
            arg->write_cont->push_back(arg->thread_num);
        }

        if (pthread_mutex_unlock(arg->mutex) != 0) {
            std::perror("mutex unlock");
        }
    }

    pthread_exit(nullptr);
}

int main(int argc, char const *argv[]) {
    std::array<thread_arg, num_thread> info_arr;
    pthread_mutex_t mutex;
    write_cont_t cont;

    if (pthread_mutex_init(&mutex, nullptr) != 0) {
        std::perror("mutex init");
    }

    for (int i = 0; i != num_thread; ++i) {
        info_arr[i] = {
            i,
            &mutex,
            &cont
        };

        if (pthread_create(&info_arr[i].thread, nullptr, start_func, &info_arr[i]) != 0) {
            std::perror("thread create");
        }
    }

    for (auto elem : info_arr) {
        if (pthread_join(elem.thread, nullptr) != 0) {
            std::perror("thread join");
        }
    }

    return 0;
}