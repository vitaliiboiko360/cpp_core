#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

const int limit = 10;

void print(const boost::system::error_code& /*ec*/, boost::asio::steady_timer* t, int* count)
{
    if (*count < limit)
    {
        std::cout << "count: " << *count << std::endl;
        ++(*count);
        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));
    }
}

int main(int argc, char** argv)
{
    boost::asio::io_context io;
    int count = 0;

    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));

    t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t, &count));

    io.run();

    std::cout<<"main ended\n";

    return 0;
}