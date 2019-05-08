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
        timer1_.async_wait(boost::bind(&printer::print, this));
    }

    ~printer()
    {
        std::cout<<"~count_: "<<count_<<"\n";
    }

    void print()
    {
        if(count_ < 5)
        {
            std::cout<<count_++<<"\n";
            timer1_.expires_at(timer_.expiry() + boost::chrono::seconds(1));
            timer1_.async_wait(boost::bind(&printer::print, this));
        }
    }

private:
    boost::asio::io_context::strand strand_;
    boost::asio::steady_timer timer1_;
    boost::asio::steady_timer timer2_;
    int count_;
};

int main()
{
    
    boost::asio::io_context io;
    printer p(io);
    io.run();

    return 0;
}