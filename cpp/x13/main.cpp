#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

class printer
{
public:
    printer(boost::asio::io_context& io)
    : strand_(io)
    , timer1_(io, boost::asio::chrono::seconds(1))
    , timer2_(io, boost::asio::chrono::seconds(1))
    , count_(0)
    {
        timer1_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print1, this)));
        timer2_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print2, this)));
    }

    ~printer()
    {
        std::cout<<boost::this_thread::get_id()<<" ~ "<<count_<<"\n";
    }

    void print1()
    {
        if(count_ < limit_)
        {
            std::cout<<boost::this_thread::get_id()<<" "<<count_++<<"\n";
            timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(1));
            timer1_.async_wait(boost::bind(&printer::print1, this));
        }
    }

    void print2()
    {
        if(count_ < limit_)
        {
            std::cout<<boost::this_thread::get_id()<<" "<<count_++<<"\n";
            timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));
            timer2_.async_wait(boost::bind(&printer::print2, this));
        }
    }

private:
    boost::asio::io_context::strand strand_;
    boost::asio::steady_timer timer1_;
    boost::asio::steady_timer timer2_;
    int count_;
    const int limit_ = 10;
};

int main()
{
    
    boost::asio::io_context io;
    printer p(io);

    boost::thread t(boost::bind(&boost::asio::io_context::run, &io));
    
    io.run();
    t.join();

    return 0;
}