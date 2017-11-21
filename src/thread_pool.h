//
// Created by zoe on 20/11/17.
//

#ifndef RACETHEMOON_THREAD_POOL_H
#define RACETHEMOON_THREAD_POOL_H

#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

using namespace std;

typedef void (*task_func)(void *arg, void *dt);

struct task_data
{
    unsigned long id;
    task_func work;
    std::vector<void*> data;
    //~task_data();
};

struct job_data
{
    queue<task_data> jobs_;
    mutex queue_mutex;
    condition_variable semaphore;
    bool kill = false;
};

class thread_pool
{
private:
    int num_;
    vector<thread> pool_;

    int idpool = 0;
    thread_pool();

public:
    job_data jd_;

    static inline std::shared_ptr<thread_pool> get()
    {
        static std::shared_ptr<thread_pool> instance = std::shared_ptr<thread_pool>(new thread_pool());
        return instance;
    }

    void init();
    void shutdown();
    void add_job(std::shared_ptr<task_data> task);
    std::shared_ptr<task_data> makeTask(task_func tf, void *arg1, void *arg2);

};


#endif //RACETHEMOON_THREAD_POOL_H
