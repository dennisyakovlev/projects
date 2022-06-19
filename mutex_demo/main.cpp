#include <iostream>
#include <pthread.h>
#include <vector>
#include <cstdio>
#include <algorithm>

/*  DEMONSTRATE: Pthread mutex lock.

    Notice how the mutex locks. It locks for the entire duration of the write
    to the vector. Thus, the vector will be half filled with size/2 consecutive
    1's and 2's. Whether 1 or 2 fills the first/second half may change, but it 
    will always have them be conescutive.

    Step 2
*/

#define SIZE 2000
#define INIT_VAL -1

using cont_t = std::vector<int>;
using cont_ptr_t = cont_t*;

pthread_mutex_t mutex;

void* func_1(void* arg) { // seperate functions for easier debugging

    cont_ptr_t vec = reinterpret_cast<cont_ptr_t>(arg);

    if (pthread_mutex_lock(&mutex) != 0) {
        std::perror("lock 1");
    }

    auto beg = std::find(vec->begin(), vec->end(), INIT_VAL);
    for (auto i = beg; i != beg + (vec->size() / 2); ++i) {
        *i = 1;
    }

    if (pthread_mutex_unlock(&mutex) != 0) {
        std::perror("unlock 1");
    }

    pthread_exit(nullptr);
}

void* func_2(void* arg) {

    cont_ptr_t vec = reinterpret_cast<cont_ptr_t>(arg);

    if (pthread_mutex_lock(&mutex) != 0) {
        std::perror("lock 2");
    }

    auto beg = std::find(vec->begin(), vec->end(), INIT_VAL);
    for (auto i = beg; i != beg + (vec->size() / 2); ++i) {
        *i = 2;
    }

    if (pthread_mutex_unlock(&mutex) != 0) {
        std::perror("unlock 2");
    }

    pthread_exit(nullptr);
}

int main(int argc, char const *argv[]) {

    std::vector<int> vec(SIZE, INIT_VAL); // is the mutex variable

    pthread_t t1, t2;

    if (pthread_mutex_init(&mutex, nullptr) != 0) {
        std::perror("init");
    }

    if (pthread_create(&t1, nullptr, func_1, &vec) != 0) {
        std::perror("create");
    }
    if (pthread_create(&t2, nullptr, func_2, &vec) != 0) {
        std::perror("create");
    }



    if (pthread_join(t1, nullptr) != 0) {
        std::perror("join");
    }

    if (pthread_join(t2, nullptr) != 0) {
        std::perror("join");
    }

    if (pthread_mutex_destroy(&mutex) != 0) {
        std::perror("destroy");
    }



    for (int i : vec) {
        std::cout << i << " ";
    }

    std::cout << std::endl;    

    return 0;
}
