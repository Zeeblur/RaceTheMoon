//
// Created by zoe on 20/11/17.
//

#include <iostream>
#include "thread_pool.h"


thread_pool::thread_pool()
{
    num_ = thread::hardware_concurrency();
    init();
}


void wait_for_tasks(job_data& tp)
{
    std::cout << "hello from thread " << std::endl;
    while(true)
    {
        unique_lock<mutex> lock(tp.queue_mutex);

        tp.semaphore.wait(lock, [&]{return !tp.jobs_.empty();});
        task_data job = tp.jobs_.front();
        tp.jobs_.pop();

        job.work(job.data[0], job.data[1]); // function<void()> type
    }
}

void thread_pool::init()
{
    for(int i = 0; i < num_; i++)
    {
        pool_.push_back(thread(wait_for_tasks, ref(jd_)));
    }
}

void thread_pool::add_job(std::shared_ptr<task_data> task)
{
    unique_lock<mutex> lock(jd_.queue_mutex);
    jd_.jobs_.push(*task);
    jd_.semaphore.notify_one();
}

std::shared_ptr<task_data> thread_pool::makeTask(task_func tf, void *arg1, void *arg2)
{
    auto t = std::make_shared<task_data>(task_data());
    t->id = idpool++;
    t->work = tf;
    t->data.push_back(arg1);
    t->data.push_back(arg2);
    return t;
}


