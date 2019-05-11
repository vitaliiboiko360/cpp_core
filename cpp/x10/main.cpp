#include <iostream>
#include <boost/asio.hpp>

void print(const boost::system::error_code& /*e*/)
{
    std::cout<<"print callback called\n";
}

int main(int argc, char **argv)
{

    boost::asio::io_context io;

    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));

    t.async_wait(&print);
    std::cout<<"we've just called t.async_wait with print callback\n";

    int number_handlers = io.run();
    std::cout<<"io.run returned num of handlers\t"<<number_handlers<<"\n";


    std::cout << "main ended" << std::endl;

    return 0;
}