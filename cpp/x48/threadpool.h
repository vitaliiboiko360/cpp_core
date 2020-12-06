#include <memory>
#include <atomic>
#include <queue>
#include <mutex>
#include <functional>

class thread_pool
{
    struct work_item;
    struct work_queue;
public:

    void add_work(std::function<void()>* p_task)
    {
        ++ma_work_count;
        m_work_queue.push_work(p_task);
    }

    void work_queue::add_work(std::function<void()>* p_task)

private:
    unsigned m_number_threads;
    std::unique_ptr<work_queue> m_work_queue;
    std::atomic<unsigned> ma_work_count{ 0 };
};

struct thread_pool::work_queue
{
    void add_work(std::function<void()>* p_task)
    {
        std::unique_lock<std::mutex> l(m_mutex_work_items);
        m_work_items.emplace(p_task);
    }

    std::mutex m_mutex_work_items;
    std::queue<work_item> m_work_items;
};

struct thread_pool::work_item
{
    work_item(std::function<void()> p_task)
    : m_task(p_task)
    {}

private:
    std::function<void()> m_task;
};